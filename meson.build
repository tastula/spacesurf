project('SpaceSurf', 'cpp')

src = [
    'src/assets.cc',
    'src/clock.cc',
    'src/effects.cc',
    'src/label.cc',
    'src/main.cc',
    'src/game.cc',
    'src/object.cc',
    'src/player.cc',
    'src/resources.cc',
    'src/stone.cc'
]

dps = [
    dependency('SDL2'),
    dependency('SDL2_image'),
    dependency('SDL2_ttf')
]

executable('surf', src, dependencies: dps)
