# DoomLikeC++Shooter

# Doomlike Shooter in CMD

A small C++ terminal-based shooter inspired by old-school **Doom** and **Wolfenstein**.

The game is intentionally kept small, with **one weapon** and **one enemy**. The main focus is the technical challenge of creating a pseudo-3D game in the terminal without using a game engine.

---

## In-depth Development

### Chosen
**Software**

### Subject
**Game development without a game engine**

### Learning Goals

- Develop a game without using a game engine.
- Create a simple pseudo-3D renderer using raycasting.
- Develop our own tools and systems for the game.
- Render efficiently within the limitations of the terminal.
- Program collision detection and player movement.
- Create a simple enemy AI and shooting system.

### Application

We are creating a small C++ terminal-based shooter in which the player can move through a simple map, use one weapon, and fight one enemy.

The world is not actually rendered in 3D. Instead, a **2D map is converted into a pseudo-3D view using raycasting**. This allows us to recreate the style and feel of classic Doom-like games while working entirely inside the terminal.

The main systems are developed ourselves instead of relying on an existing game engine, including:

- Player movement
- Collision detection
- Raycasting
- Pseudo-3D rendering
- Shooting
- Enemy AI
- Terminal rendering

### Why This In-depth Development?

Developing a game without an engine requires many technical systems to be created from scratch. Instead of using existing solutions for rendering, collision, and movement, these systems have to be researched and developed ourselves.

The limited scope of **one enemy and one weapon** keeps the project manageable and allows us to focus on the technical side of game development.

---

# User Stories

## User Story 1 — Player Movement and Collision

**User Story:**  
As a player, I want to move around the map so that I can explore the world.

**Feature:**  
Player movement and collision.

**Tasks:**
- Create keyboard input.
- Add forward, backward, and sideways movement.
- Create collision detection with walls.
- Prevent the player from walking through walls.

**Test:**  
The player can move in all directions and stops when they collide with a wall.

**Priority:**  
**Must-have**

---

## User Story 2 — Raycasting / Pseudo-3D Rendering

**User Story:**  
As a player, I want to see the map in pseudo-3D so that the game feels like a Doom-like shooter.

**Feature:**  
Raycasting / pseudo-3D rendering.

**Tasks:**
- Store the map as a 2D grid.
- Cast rays from the player.
- Calculate the distance to walls.
- Draw walls based on their distance.
- Add camera rotation.

**Test:**  
The walls are correctly displayed as a pseudo-3D environment and change when the player rotates.

**Priority:**  
**Must-have**

---

## User Story 3 — Shooting System

**User Story:**  
As a player, I want to use my weapon to attack the enemy.

**Feature:**  
Shooting system.

**Tasks:**
- Create one weapon.
- Add shooting input.
- Create hitscan / ray-based shooting.
- Apply damage to the enemy.
- Add shooting feedback.

**Test:**  
When the player shoots, an enemy in the direction of the shot is hit and loses HP.

**Priority:**  
**Must-have**

---

## User Story 4 — Enemy AI

**User Story:**  
As a player, I want to fight an enemy so that there is a clear gameplay loop.

**Feature:**  
Enemy AI.

**Tasks:**
- Create one enemy.
- Program enemy movement.
- Detect when the enemy can see the player.
- Make the enemy move towards the player.
- Make the enemy damage the player when attacking.
- Create a death state.

**Test:**  
The enemy can detect, follow, and attack the player. When the enemy reaches 0 HP, it dies or disappears.

**Priority:**  
**Must-have**

---

## User Story 5 — Health System

**User Story:**  
As a player, I want to see how much health I have left so that I know when I am going to die.

**Feature:**  
Health system.

**Tasks:**
- Add player HP.
- Program damage reception.
- Display HP in the terminal.
- Create a death state.

**Test:**  
When the enemy attacks, the player's HP decreases. When HP reaches 0, the game ends.

**Priority:**  
**Must-have**

---

## User Story 6 — Terminal Rendering Optimization

**User Story:**  
As a developer, I want to render the terminal efficiently so that the game remains playable.

**Feature:**  
Terminal rendering optimization.

**Tasks:**
- Create a screen buffer.
- Prevent unnecessary redrawing of the entire screen.
- Optimize the render loop.
- Monitor FPS / update timing.

**Test:**  
The game continues to respond smoothly while moving and rendering the environment.

**Priority:**  
**Should-have**

---

## User Story 7 — Custom Game Systems

**User Story:**  
As a developer, I want to use my own tools and systems so that I can build the game without an engine.

**Feature:**  
Custom game framework / tools.

**Tasks:**
- Create a custom input system.
- Create a custom renderer.
- Create a custom map structure.
- Create the game loop.
- Separate the player, enemy, and shooting systems.

**Test:**  
The main game functionality works without Unity, Unreal, or another game engine.

**Priority:**  
**Must-have**

---

## User Story 8 — Win / Lose Conditions

**User Story:**  
As a player, I want to be able to complete the game so that there is a clear beginning and ending.

**Feature:**  
Win/lose conditions.

**Tasks:**
- Detect enemy death.
- Add a win condition.
- Detect player death.
- Create a lose screen.
- Add a restart or exit option.

**Test:**  
The game ends when the enemy is defeated or the player dies.

**Priority:**  
**Should-have**

---

## User Story 9 — Combat Feedback

**User Story:**  
As a player, I want simple feedback when I hit the enemy so that my actions are clear.

**Feature:**  
Combat feedback.

**Tasks:**
- Add hit feedback in the terminal.
- Display enemy HP or provide hit feedback.
- Add a shooting cooldown.
- Optionally create a simple muzzle/fire effect using ASCII.

**Test:**  
The player can clearly see when a shot is fired and when the enemy is hit.

**Priority:**  
**Could-have**

---

# Sprint Planning

## Sprint 1 — Core Development

### Sprint Goal

Create a playable prototype where the player can move around a small map, collide with walls, and see the environment through basic pseudo-3D raycasting.

### User Stories

- User Story 7 — Custom Game Systems
- User Story 2 — Raycasting / Pseudo-3D Rendering
- User Story 1 — Player Movement and Collision

### Sprint Tasks

1. Set up the C++ project.
2. Create the game loop.
3. Create terminal keyboard input.
4. Create the map structure.
5. Add the player's position and rotation.
6. Implement player movement.
7. Add collision detection.
8. Create the raycasting system.
9. Create pseudo-3D wall rendering.
10. Add a basic screen buffer.
11. Test movement, collision, and rendering.
12. Combine all systems into the main game loop.

### Sprint 1 Result

A playable prototype where the player can move around a small map, cannot walk through walls, and can view the environment as a basic pseudo-3D scene.

---

## Sprint 2 — Gameplay Development

### Sprint Goal

Turn the core prototype into an actual shooter with one weapon, one enemy, and a complete gameplay loop.

### User Stories

- User Story 3 — Shooting System
- User Story 4 — Enemy AI
- User Story 5 — Health System
- User Story 8 — Win / Lose Conditions

### Sprint Tasks

- Further develop the shooting system.
- Add one weapon.
- Add hitscan shooting.
- Create one enemy.
- Create enemy movement and detection.
- Add enemy attacks.
- Add enemy HP.
- Add player HP.
- Add enemy death.
- Add player death.
- Add win and lose conditions.
- Test the complete gameplay loop.

### Sprint 2 Result

A complete small gameplay loop where the player can move, shoot, defeat the enemy, take damage, and die.

---

## Sprint 3 — Polish and Delivery

### Sprint Goal

Make the game stable, efficient, readable, and ready for presentation.

### User Stories

- User Story 6 — Terminal Rendering Optimization
- User Story 9 — Combat Feedback
- Improvements to previous user stories

### Sprint Tasks

- Fix bugs and technical issues.
- Improve movement and shooting.
- Improve terminal rendering and performance.
- Add clear shooting and hit feedback.
- Improve terminal UI readability.
- Test the complete game.
- Create the final build.
- Prepare the presentation.
- Prepare an explanation of the custom systems.

### Sprint 3 Result

A stable and polished Doomlike terminal shooter ready for presentation.

---

# Sprint 1 — Detailed Development Plan

## 1. Set Up the C++ Project

### Build
- Create the C++ project.
- Set up the main `.cpp`.
- Create the main game loop.
- Set up the terminal window and screen size.

### Test
- The program starts and stays running.
- The game loop updates continuously.

### Result
An empty but functional game framework.

---

## 2. Create the Terminal Input System

### Build
- Detect keyboard input without requiring Enter.
- Add `WASD` for movement.
- Add left/right controls for rotation.
- Separate input handling from the game loop.

### Test
- Pressing a key produces the expected input.
- Multiple inputs do not break the game.

### Result
The game can receive real-time player input.

---

## 3. Create the Map

### Build
- Store the level as a 2D array/grid.
- Use simple characters:
  - `#` = wall
  - `.` = empty space
- Create a small test map.
- Add a player starting position.

Example:

```text
##########
#........#
#..##....#
#........#
#....#...#
#........#
##########
```

### Test
- The map loads correctly.
- The player starts at the correct location.
- Walls and empty spaces are correctly recognized.

### Result
A basic playable map exists internally.

---

## 4. Create Player Movement

### Build
- Add player X and Y position.
- Add movement speed.
- Calculate movement from player direction.
- Add player rotation.

### Test
- The player moves forward and backward.
- The player can turn.
- Movement feels consistent.

### Result
The player can move around the 2D map.

---

## 5. Add Collision Detection

### Build
- Check the next player position before moving.
- Detect whether the destination is a wall.
- Prevent movement through walls.

### Test
- Walking into a wall stops the player.
- The player can move normally through open areas.
- The player cannot leave the map.

### Result
The player can safely navigate the map.

---

## 6. Create the Raycasting System

### Build
- Create a ray for every terminal column.
- Calculate the ray direction based on the player's direction and FOV.
- Check where each ray hits a wall.
- Calculate the distance to the wall.

### Test
- Rays correctly detect walls.
- Closer walls produce smaller distances.
- Rotating the player changes the ray directions.

### Result
The game can calculate the pseudo-3D view.

---

## 7. Render the Pseudo-3D Environment

### Build
- Convert wall distance into wall height.
- Draw the wall height in the terminal.
- Add a ceiling and floor if needed.
- Use ASCII characters for shading.

Example:

```text
       ########
    ##############
  ##################
######################
######################
######################
```

### Test
- Walls appear taller when closer.
- Walls become smaller when farther away.
- Turning the player changes the visible environment.
- The rendering does not completely break when moving.

### Result
A basic Doom-like pseudo-3D environment.

---

## 8. Optimize the Terminal Rendering

### Build
- Create a screen buffer.
- Build the entire frame in memory first.
- Output the frame at once instead of printing every character individually.
- Add basic frame/update timing.

### Test
- The screen does not flicker excessively.
- Movement and rotation remain responsive.
- The terminal does not become noticeably slower during rendering.

### Result
A more stable and efficient renderer.

---

## 9. Combine Everything

At the end of Sprint 1, connect:

```text
Input
  ↓
Player Movement
  ↓
Collision
  ↓
Raycasting
  ↓
Rendering
  ↓
Game Loop
  ↓
Repeat
```

### Sprint 1 Final Test

The Sprint 1 build is successful when:

- The game runs directly in the terminal.
- The player can move and rotate.
- The player cannot walk through walls.
- The map is correctly loaded.
- The environment is displayed using raycasting.
- The pseudo-3D view changes when the player moves or rotates.
- The renderer remains reasonably responsive.

### Sprint 1 Final Product

A small map with:

**Playable movement + collision + working raycasting + pseudo-3D terminal rendering**

The enemy and combat systems are left for **Sprint 2**.
