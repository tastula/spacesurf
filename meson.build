project('SpaceSurf', 'cpp')

src = [
    'src/assets.cc',
    'src/clock.cc',
    'src/effects.cc',
    'src/hud.cc',
    'src/label.cc',
    'src/level.cc',
    'src/main.cc',
    'src/menu.cc',
    'src/game.cc',
    'src/gameobject.cc',
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
