from cx_Freeze import setup, Executable

# Dependencies are automatically detected, but it might need
# fine tuning.
buildOptions = dict(packages = [], excludes = [])

base = 'Console'

executables = [
    Executable('D:\\code\\server_v20150413\\code\\source\\libdawn\\py\\py_http_server.py', base=base)
]

setup(name='py',
      version = '1.0',
      description = 'for panda',
      options = dict(build_exe = buildOptions),
      executables = executables)
