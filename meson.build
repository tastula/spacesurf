project('SpaceSurf', 'cpp')

src = [
    'src/clock.cc',
    'src/label.cc',
    'src/main.cc',
    'src/game.cc',
    'src/object.cc',
    'src/resources.cc'
]

dps = [
    dependency('SDL2'),
    dependency('SDL2_image'),
    dependency('SDL2_ttf')
]

executable('surf', src, dependencies: dps)
