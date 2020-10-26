import os, sys
from conans import ConanFile, tools, CMake

class metaConan(ConanFile):
    name = "meta"
    settings = "os", "compiler", "build_type", "arch"
    description = "a C++ metaprogramming lib"
    url = "https://github.com/vermosen/meta.git"
    license = "None"
    author = "vermosen@yahoo.com"
    topics = None
    generators = 'cmake'
    cmake_files = ['%sConfig.cmake' % name,
                   '%sConfigVersion.cmake' % name,
                   '%sTargets.cmake' % name,
                   '%sTargets-*.cmake' % name]

    _source_subfolder = name
    _build_subfolder = 'build'
    _runbuild = False

    def source(self):
        self.run('git clone --recursive %s' % self.url)

    def requirements(self):
        self.requires("gtest/1.8.1@%s/%s" % (self.user, self.channel))
        
    def _configure_cmake(self):
        cmake = CMake(self, set_cmake_flags=True)
        
        if self.settings.compiler == 'gcc':
            if self.settings.compiler.version in ['8', '8.4']:
                cmake.definitions["CMAKE_PROFILE"] = 'gcc84'
            elif self.settings.compiler.version in ['9', '9.3']:
                cmake.definitions["CMAKE_PROFILE"] = 'gcc93'
            else:
                self.output.info('compiler %s %s not supported' % 
                  (self.settings.compiler, self.settings.compiler.version))
        else:
            exit(1)

        # cannot run conan command inside the build process
        cmake.definitions["SKIP_CONAN_PACKAGE"] = 'ON'
        cmake.configure(source_folder=self._source_subfolder)
        return cmake

    def build(self):
        self._runbuild = True
        cmake = self._configure_cmake()
        cmake.build()
        cmake.install()

    def package(self):
        self.output.info('executing packaging in folder %s' % os.getcwd())
        hdrloc = 'meta/include' if self._runbuild else 'include'
        self.copy("*.h"  , dst="include", src=hdrloc)

        if self.settings.os == 'Linux':
            try:
                path = "%s/%sTargets.cmake" % (self.build_folder, self.name)

                with open(path) as f:
                    content = f.read()
                    self.output.info('read %sTargets.cmake content [size=%s]' % (self.name, len(content)))

                import re, glob
                m = re.search(r'set\(_IMPORT_PREFIX \"([^\"]+)\"\)', content)
                self.output.info('found prefix value: %s' % m.group(1))
                files = glob.glob('%s/*Targets*.cmake' % self.build_folder)

                for f in files:
                    self.output.info('replacing prefix path in %s' % f)
                    tools.replace_in_file(f, m.group(1),
                        '${CONAN_%s_ROOT}' % self.name.upper(), strict=False)

                # step 2: substitute LIB_PATH
                with open("%s/%sConfig.cmake" % (self.build_folder, self.name)) as f:
                    content = f.read()
                    self.output.info('read %sConfig.cmake content [size: %s]' % (self.name, len(content)))
                    rgx = r'set\s*\(%s_CONAN_LIBS_DIRS_HINT\s+\"*([^\"]+)\"*\s*\)' % self.name.upper()
                    self.output.info('looking for regex %s' % rgx)
                    m = re.search(rgx, content)

                    if m is not None:
                        self.output.info('found lib install location: %s' % m.group(1))
                    else:
                        self.output.error('failed to parse file content %s' % content)
                        raise
                
                    for f in files:
                        self.output.info('replacing lib install location in %s' % f)
                        tools.replace_in_file(f, m.group(1),
                            '${CONAN_%s_ROOT}/lib' % self.name.upper(), strict=False)

                # step 3: copy the cmake config files
                self.output.info('looking for modified files in %s ...' % os.getcwd())

                for f in self.cmake_files:
                    self.copy("%s" % f, src=self.build_folder, keep_path=False)

            except:
                self.output.error('failed to parse cmake install files: %s' % sys.exc_info()[0])

    def package_info(self):
        self.cpp_info.includedirs = ['include']
