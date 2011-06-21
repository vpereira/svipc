import Options, Utils
from os import unlink, symlink, chdir
from os.path import exists

srcdir = '.'
blddir = 'build'
VERSION = '0.0.1'

def set_options(opt):
  opt.tool_options('compiler_cxx')

def configure(conf):
  conf.check_tool('compiler_cxx')
  conf.check_tool('node_addon')
  conf.env.append_unique('CXXFLAGS', ["-Wall"])


def build(bld):
  obj = bld.new_task_gen('cxx', 'shlib', 'node_addon')
  obj.target = 'svipc'
  obj.source = './src/svipc.cc'

def shutdown():
  if Options.commands['clean']:
    if exists('svipc.node'): unlink('svipc.node')
  else:
    if exists('build/default/svipc.node') and not exists('svipc.node'):
      symlink('build/default/svipc.node', 'svipc.node')

