import os
import yaml
import tarfile
import requests
import shutil
import jinja2

def file_get_contents(filename, encoding=None):
    with open(filename, mode='r', encoding=encoding) as fh:
        return fh.read()

def copy_from_commit():
    tar_name = 'slh_dsa_c.tar.gz'
    tar_path = os.path.join(slh_dir, tar_name)

    for entry in os.listdir(slh_dir):
        full_path = os.path.join(slh_dir, entry)
        if os.path.isdir(full_path):
            shutil.rmtree(os.path.join(full_path))

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

# os.environ['LIBOQS_DIR'] = '/Users/h2parson/Documents/liboqs'
commit_hash = "a8e4b8b9991a8e21a1e652345e1a2030e9503ea7"
slh_dir = os.path.join(os.environ['LIBOQS_DIR'], 'src/sig/slh_dsa')
slh_dsa_c_dir = os.path.join(slh_dir, 'slh_dsa_c')
meta_file = os.path.join(slh_dsa_c_dir, 'integration/META.yml')
jinja_src_file = os.path.join(slh_dir, 'slh_dsa_src_template.jinja')

copy_from_commit()

meta = file_get_contents(meta_file, encoding='utf-8')
meta = yaml.safe_load(meta)

template = file_get_contents(jinja_src_file)
impl = {
  "pure": True,
  "paramSet": "",
  "hashAlg": "",
  "prehashHashAlg": "",
  "pkSize": "",
  "skSize": "",
  "sigSize": ""
}

# pure variants only
for paramSet in meta['paramSets']:
    impl['paramSet'] = paramSet['name']
    impl['pkSize'] = paramSet['pkSize']
    impl['skSize'] = paramSet['skSize']
    impl['sigSize'] = paramSet['sigSize']

    for hashAlg in meta['hashAlgs']:
        impl['hashAlg'] = hashAlg['name']

        output = jinja2.Template(template).render(impl)

        src_file = 'slh_dsa_pure_' + impl['hashAlg'] + '_' + impl['paramSet'] + '.c'
        src_path = os.path.join(slh_dir, src_file)
        
        with open(src_path, "w") as f:
            f.write(output)

