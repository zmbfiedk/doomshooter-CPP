
# DoomLikeC++Shooter

Press `1`, `2`, or `3` to switch between the pistol, shotgun, and rifle. Hold
`Space` to fire using a center-screen raycast. Press `R` to reload the selected
weapon; each weapon has its own magazine and reserve ammunition.

One stationary red enemy is placed in the map. Center shots damage it only when
it is in front of the first wall hit. While alive and visible, it periodically
damages the player. The HUD shows health, magazine ammo, reserve ammo, reload
progress, and a center crosshair. Player movement and combat stop when health
reaches zero.
