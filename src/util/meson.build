
util_deps = []

util_src = files(
    'assert.c',
    'crap.c',
    'env.c',
    'fbpair.c',
    'geometry.c',
    'graphics.c',
    'io.c',
    'kvparser.c',
    'miscmath.c',
    'pixmap.c',
    'pngcruft.c',
    'rectpack.c',
    'stringops.c',
)

util_opus_src = files(
    'opuscruft.c',
)

sse42_src += files(
    'sse42.c',
)

if is_developer_build
    util_src += files('debug.c')
endif

config.set('TAISEI_BUILDCONF_USE_DESIGNATED_INIT', cc.compiles(
    'struct { int dummy; } __attribute__((designated_init)) x;',
    name : '__attribute__((designated_init)) with -Werror',
    args : ['-Wattributes', '-Werror']
))

use_libcrypto = get_option('use_libcrypto')

if use_libcrypto == 'auto'
    use_libcrypto = dep_crypto.found()
else
    use_libcrypto = (use_libcrypto == 'true')
endif

if use_libcrypto
    assert(dep_crypto.found(), 'use_libcrypto forced but libcrypto not found. Install OpenSSL or disable use_libcrypto.')
    util_src += files('sha256_openssl.c')
    util_deps += [dep_crypto]
else
    util_src += files('sha256.c')
endif

if host_machine.system() == 'windows'
    # NOTE: Even if we ever build this with something like Midipix, we'd
    # probably still want to use the winapi implementation of this here.
    util_src += files('platform_win32.c')
else
    # No have_posix check, it might just work.
    util_src += files('platform_posix.c')
endif

subdir('pixmap_loaders')
util_src += pixmap_loaders_src
