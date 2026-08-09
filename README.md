# Rotation Screen

**Rotation Screen** is a Geometry Dash mod that adds a chaotic visual challenge by randomly rotating your screen to different angles (0°, 90°, 180°, or 270°) while playing.

---

### About

The mod picks a new random angle that is different from the current one and smoothly rotates the play layer. It then automatically schedules the next rotation using a randomized delay based on your settings.

### Key Features

* **Random Rotations**: Rotates your view to 0°, 90°, 180°, or 270° at randomized intervals.

* **Pause Safe**: Detects when the game is paused and postpones rotations to prevent glitches or camera desync.

* **Auto Reset**: Instantly resets the screen back to 0° when dying or restarting the level (`resetLevel`).

* **Action Safety**: Uses separate action tags for the rotation timer and animation, preventing the mod from interfering with other actions running on the play layer.

### Configuration

You can adjust the following parameters directly from the **Geode** settings menu:

* **Min interval (seconds)**: Minimum wait time before the screen rotates.

* **Max interval (seconds)**: Maximum wait time before the screen rotates.

* **Rotation animation duration**: How long the screen takes to complete each rotation, in seconds.

---

*Created by **DalingYT***
