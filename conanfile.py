from conans import ConanFile, CMake, tools


class HelloConan(ConanFile):
    name = "VideoWriter"
    version = "1.3"
    license = "BSD-2"
    url = "https://github.com/gcjyzdd/Simple-Video-Writter"
    description = "A simple video writer wrapped OpenCV"
    settings = "os", "compiler", "build_type", "arch"
    options = {}
    default_options = {}
    generators = "cmake"

    def config_options(self):
        self.settings.build_type = "Release"
        if self.settings.os == "Windows":
            self.settings.compiler.runtime = "MD"

    def build(self):
        pass

        # Explicit way:
        # self.run('cmake %s/hello %s'
        #          % (self.source_folder, cmake.command_line))
        # self.run("cmake --build . %s" % cmake.build_config)

    def package(self):
        cmake = CMake(self)
        cmake.configure()
        if self.settings.os != "Windows":
            self.run("cmake --build . --config Release -j")
        else:
            self.run("cmake --build . --config Release")
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["videowriter"]
