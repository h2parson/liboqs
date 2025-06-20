import os
import yaml
import tarfile
import requests
import shutil
import jinja2
import glob

def file_get_contents(filename, encoding=None):
    with open(filename, mode='r', encoding=encoding) as fh:
        return fh.read()

def copy_from_commit():
    tar_name = 'slh_dsa_c.tar.gz'
    tar_path = os.path.join(slh_dir, tar_name)

    #clean up code
    shutil.rmtree(os.path.join(slh_dsa_c_dir))

    url = os.path.join('https://github.com/pq-code-package/slhdsa-c/archive/', commit_hash, ".tar.gz")

    response = requests.get(url) 

    if response.status_code == 200:
        os.makedirs(slh_dir, exist_ok=True)

        with open(tar_path, 'wb') as file:
            file.write(response.content)

        tar_file = tarfile.open(tar_path) 
        tar_file.extractall(slh_dir) 
        tar_file.close()
        os.remove(tar_path)

        for entry in os.listdir(slh_dir):
            if entry[:6] == 'slhdsa':
                full_path = os.path.join(slh_dir, entry)
                if os.path.isdir(full_path):
                    os.rename(full_path, slh_dsa_c_dir)

        print('Copied from slh dsa commit succesfully')
    else:
        print('Failed to copy from slh dsa commit')

def section_bound(identifier, delimiter, text, side):
    searchString = delimiter + ' OQS_COPY_FROM_SLH_DSA_FRAGMENT_' + identifier + '_' + side
    res = text.find(searchString)
    if side == 'START':
        res += len(searchString)
    return res

def replacer(template_file, destination_file, identifier, variants):
    #get section at identifier in template
    template = file_get_contents(template_file)
    section = template[section_bound(identifier,'/////',template,'START'):section_bound(identifier,'/////',template,'END')]
    
    #get preamble/postamble in destination file
    destination = file_get_contents(destination_file)
    preamble = destination[:section_bound(identifier,'/////',destination,'START')]
    postamble = destination[section_bound(identifier,'/////',destination,'END'):]

    #replace destination section with rendered template
    contents = preamble + jinja2.Template(section).render(variants) + postamble
    with open(template_file, "w") as f:
                f.write(contents)

def internal_code_gen():
    #clean up code
    shutil.rmtree(slh_wrappers_dir)

    #Start Header File and Setup
    header_template = file_get_contents(jinja_header_file)
    
    header_section = header_template[section_bound('0','####', header_template,'START'):section_bound('0','####',header_template,'END')]
    header_contents = jinja2.Template(header_section).render()
    
    src_template = file_get_contents(jinja_src_file)
    header_section = header_template[section_bound('BODY','####',header_template,'START'):section_bound('BODY','####',header_template,'END')]
    
    # Create Src Files for Pure variants
    for paramSet in meta['paramSets']:
        impl['paramSet'] = paramSet['name']
        impl['pkSize'] = paramSet['pkSize']
        impl['skSize'] = paramSet['skSize']
        impl['sigSize'] = paramSet['sigSize']
    
        for hashAlg in meta['hashAlgs']:
            impl['hashAlg'] = hashAlg['name']
    
            src_contents = jinja2.Template(src_template).render(impl)
    
            src_file = 'slh_dsa_pure_' + impl['hashAlg'] + '_' + impl['paramSet'] + '.c'
            src_path = os.path.join(slh_wrappers_dir, 'pure', src_file)
            os.makedirs(os.path.dirname(src_path),exist_ok=True)
            
            with open(src_path, "w") as f:
                f.write(src_contents)
    
            header_contents += jinja2.Template(header_section).render(impl)
    
    # Create Src Files for Prehash variants
    impl['pure'] = False
    
    for paramSet in meta['paramSets']:
        impl['paramSet'] = paramSet['name']
        impl['pkSize'] = paramSet['pkSize']
        impl['skSize'] = paramSet['skSize']
        impl['sigSize'] = paramSet['sigSize']
    
        for hashAlg in meta['hashAlgs']:
            impl['hashAlg'] = hashAlg['name']
    
            for prehashHashAlg in meta['prehashHashAlgs']:
                impl['prehashHashAlg'] = prehashHashAlg['name']
    
                src_contents = jinja2.Template(src_template).render(impl)
    
                src_file = 'slh_dsa_' + impl['prehashHashAlg'] + '_prehash_' + impl['hashAlg'] + '_' + impl['paramSet'] + '.c'
                src_path = os.path.join(slh_wrappers_dir, 'prehash_' + prehashHashAlg['name'], src_file)
                os.makedirs(os.path.dirname(src_path),exist_ok=True)
    
                with open(src_path, "w") as f:
                    f.write(src_contents)
    
                header_contents += jinja2.Template(header_section).render(impl)
    
    #finish header file
    header_section = header_template[section_bound('2','####',header_template,'START'):section_bound('2','####',header_template,'END')]
    header_contents += jinja2.Template(header_section).render()
    header_file = "sig_slh_dsa.h"
    header_path = os.path.join(slh_dir, header_file)
    with open(header_path, "w") as f:
                f.write(header_contents)

def internal_cmake_gen():
    sources = [
        os.path.relpath(file, start=slh_dir)
        for file in glob.glob(os.path.join(slh_dir, '**', '*.c'), recursive=True)
        if 'slh_dsa_c/test/' not in os.path.relpath(file, start=slh_dir)
    ]
    prehashHashAlgs = [prehashHashAlg['name'] for prehashHashAlg in meta['prehashHashAlgs']]

    cmake_template = file_get_contents(jinja_cmake_file)
    cmake_contents = jinja2.Template(cmake_template).render({"sources": sources,
                                                            "prehashHashAlgs": prehashHashAlgs})
    cmake_file = "CMakeLists.txt"
    cmake_path = os.path.join(slh_dir, cmake_file)
    with open(cmake_path, "w") as f:
                f.write(cmake_contents)




#initialize globals
os.environ['LIBOQS_DIR'] = '/Users/h2parson/Documents/liboqs'
commit_hash = "300e124693d96b8ab0c7bd12e66dffe3cb704774"

# internal paths
slh_dir = os.path.join(os.environ['LIBOQS_DIR'], 'src/sig/slh_dsa')
slh_dsa_c_dir = os.path.join(slh_dir, 'slh_dsa_c')
slh_wrappers_dir = os.path.join(slh_dir, 'wrappers')
template_dir = os.path.join(slh_dir, 'templates')

#ensure these paths exist
os.makedirs(slh_dir,exist_ok=True)
os.makedirs(slh_dsa_c_dir,exist_ok=True)
os.makedirs(slh_wrappers_dir,exist_ok=True)
os.makedirs(template_dir,exist_ok=True)

# internal files
meta_file = os.path.join(slh_dsa_c_dir, 'integration/META.yml')
jinja_header_file = os.path.join(template_dir, 'slh_dsa_header_template.jinja')
jinja_src_file = os.path.join(template_dir, 'slh_dsa_src_template.jinja')
jinja_cmake_file = os.path.join(template_dir, 'slh_dsa_cmake_template.jinja')

#start actual code
copy_from_commit()

#load meta file
meta = file_get_contents(meta_file, encoding='utf-8')
meta = yaml.safe_load(meta)

#Create implementation dictionary
impl = {
  "pure": True,
  "paramSet": "",
  "hashAlg": "",
  "prehashHashAlg": "",
  "pkSize": "",
  "skSize": "",
  "sigSize": ""
}

#generate internal c and h files
internal_code_gen()

#generate internal cmake file
internal_cmake_gen()

#generate sig.c
sig_c_path = os.path.join(os.environ['LIBOQS_DIR'],'src','sig','sig.c')


