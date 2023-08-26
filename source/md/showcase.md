# Showcase : Sample Game {#showcase}

![FumoEngine](https://imgur.com/yE7MuA3.png)
## FUMONIA

A simple 2D survival shooter game where you can fire bullets at a never ending horde of fumos! The goal is to survive for 60 seconds before your lives run out!

<hr><br>

### Controls
` Mouse ` move cursor around to aim. <br>
`[ W ][ A ][ S ][ D ]` to move around, you can go out of bounds but you probably won't survive. <br>
`[ Space ]/[ Left Mouse Button ]` to fire bullets (Hold Down). <br>
`[ R ]` when game is over to restart the level. <br>
`[ E ]` to toggle collider visibility.

<hr><br>

### Rules
- Lives are shown at the bottom, player has 3 lives.
- The bar above is the timer, once the blue runs out and the you live, you win.
- Tab to pause, indication is shown in the window title.

<hr><br>

### Funky Features
- A simple object pooling system for both bullets and enemies
    - All the objects are initialized at start and stored in a queue.
    - Several functions are used to enqueue and dequeue them in the scene.
        - `static void EnqueueBullet(Fumo::GameObject* obj);`
        - `static Fumo::GameObject* DequeueBullet();`
        - `static void EnqueueEnemy(Fumo::GameObject* obj);`
        - `static Fumo::GameObject* DequeueEnemy();`
    - They are never destroyed so there are less read access violation issues.
<br>

- Game objects are given a bool to determine if they are active or inactive (I guess it's part of the engine) to just turn them off but not destroying them
that's how the object pool is maintained. When inactive, objects will not run update() and render() only.
<br>

- The timer is done using the progress bar with it extruding from the center horizontally, this makes it easier to identify that it's just a timer and showcases the capability of the progress bar.
<br>

- Random number generators of int and float are also used to keep things randomized and intersting. Namely, `GenerateRandomFloat(float min, float max)` and `GenerateRandomInt(int min, int max)` which utilizes the Mersenne Twister random number generator.