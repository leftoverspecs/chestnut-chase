from conans import ConanFile

class NinjaBashConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"

    def requirements(self):
        self.requires("sdl/2.26.1")
        self.requires("sdl_image/2.0.5")
        self.requires("sdl_mixer/2.0.4")
        self.requires("glew/2.2.0")
        self.requires("glm/cci.20220420")
        self.requires("ogg/1.3.5")
        if self.settings.os == "Linux":
            self.requires("libalsa/1.2.7.2")
        #openssl/1.1.1n
        #zlib/1.2.13

    def configure(self):
        self.options['sdl_image'].gif = False
        self.options['sdl_image'].lbm = False
        self.options['sdl_image'].pcx = False
        self.options['sdl_image'].pnm = False
        self.options['sdl_image'].shared = False
        self.options['sdl_image'].svg = False
        self.options['sdl_image'].tga = False
        self.options['sdl_image'].with_libjpeg = False
        self.options['sdl_image'].with_libtiff = False
        self.options['sdl_image'].with_libwebp = False
        self.options['sdl_image'].xcf = False
        self.options['sdl_image'].xpm = False
        self.options['sdl_image'].xv = False
        self.options['sdl'].shared = False
        self.options['sdl'].vulkan = False
        self.options['sdl_mixer'].mikmod = False
        self.options['sdl_mixer'].mad = False
        self.options['sdl_mixer'].modplug = False
        self.options['sdl_mixer'].mpg123 = True
        self.options['sdl_mixer'].nativemidi = False
        self.options['sdl_mixer'].flac = False
        self.options['sdl_mixer'].fluidsynth = False
        self.options['sdl_mixer'].shared = False
        if self.settings.os == 'Linux':
            self.options['sdl_mixer'].tinymid = False
            self.options['libalso'].shared = True
