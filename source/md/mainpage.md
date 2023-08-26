# User Manual {#mainpage}

![FumoEngine](https://imgur.com/yE7MuA3.png)
## Fumo Engine

Welcome to the funky manual of Fumo Engine or Fumo for short. This manual will guide you through the process of using the engine to create scenes, custom components, use built-in components all the way to building a game!

#### Engine wide Controls
`[ Tab ]` to pause/unpause application. <br>
`[ Esc ]` to exit applicaiton.

#### Made By
0133532 Lim Jun Jie

<hr><br>

## Table of Contents
1. [Introduction](#introduction)
2. [Creating Scenes](#creating-scenes)
3. [Custom Components](#custom-components)
4. [Tying scene and components](#tyingit)
5. [Core Game Engine Components](#core-game-engine-components) 
    - [TransformComponent](#transformcomponent)
    - [SpriteRenderer](#spriterenderer)
    - [RendererComponent](#renderercomponent)
    - [ProgressBar](#progressbar)
    - [CircleCollider](#circlecollider)
    - [Resource Management](#resource-management)
6. [Conclusion](#conclusion)
7. [Acknowledgements](#acknowledgement)

<hr><br>

## Introduction {#introduction}

Introducing the Fumo Engine – a practical toolkit tailored for indie game developers. With a focus on simplicity and functionality, it offers essential tools for your game development needs. Whether you're an experienced developer or new to the scene, the Fumo Engine provides a solid foundation for crafting 2D games with features like colliders and user interfaces. Streamline your development process and bring your game ideas to life with the Fumo Engine.

<hr><br>

## Creating Scenes {#creating-scenes}

Every game needs a scene. They represent different levels, menus, or gameplay segments. Here's how you can create your own scene in Fumo Engine:

1. Define your own New Scene Class
2. Add the Scene to the Scene State Machine
3. Implement Scene-Specific Logic
4. Transitions Between Scenes
<br>

1. To create a new scene, you'll need to define a new class that inherits from the BaseScene class. This class will encapsulate the logic, assets, and elements specific to the scene you're creating.
```cpp
    // Example: MyScene.h
    #include "BaseScene.h"

    class MyScene : public BaseScene {
    public:
        MyScene() {} // Constructor

        std::string getName() const override {
        return "MyScene"; // Return the name of the scene
        }

    protected:
        void initialize() override {
        // Initialize assets, game objects, and other scene-specific elements here
        }
        void on_activate() override{
        // Runs on activate, similar to initialize but comes after it
        }
        void on_deactivate() override{
        // Runs on deactivate
        }
        void on_update(float deltaTime) override{
        // Runs logic every frame
        }
        void on_render() override{
        // Similar to on_update but is mostly used to define rendering functions
        }
    };
```
<br>

2. Use the addScene() method from the SceneStateMachine class to add the newly created scene class. This ensures that your scene is properly managed by the engine.
```cpp
    // Adding the scene to SceneStateMachine, this should be done in Application.cpp
    MyScene* myScene = SceneStateMachine::addScene<MyScene>();
```
<br>

3. Inside your scene cpp class, implement the necessary functions such as initialize(), on_activate(), on_deactivate(), on_update(), and on_render(). These functions allow you to define how the scene behaves during different stages of its lifecycle.
```cpp
    // MyScene.cpp
    void MyScene::initialize() {
    // Initialize assets, game objects, and other scene-specific elements here
    }

    void MyScene::on_activate() {
    // Activate logic specific to this scene
    }

    void on_deactivate() 
    {
    // Runs on deactivate
    }

    void MyScene::on_update() {
    // Runs logic every frame
    }

    void MyScene::on_render() override{
    // Similar to on_update but is mostly used to define rendering functions
    }
    // ... Other scene-specific functions
```
<br>

4. You can transition between scenes by using the loadScene() method provided by the SceneStateMachine class. This allows you to switch from one scene to another based on specific events or conditions.
```cpp
    // Transitioning to MyScene by name (!Note: Name defined in getName(), not the class itself)
    SceneStateMachine::loadScene("MyScene");
```

<hr><br>

## Custom Components {#custom-components}

Custom components allow you to add unique behaviors and functionality to your game objects.

1. Define a New Component Class: Create a new class that inherits from the BaseComponent class. This will serve as the foundation for your custom component. Make sure to include the necessary headers and forward declarations.

```cpp
    #pragma once
    #include "BaseComponent.h"

    class CustomComponent : public BaseComponent {
    public:
    CustomComponent(GameObject* go);
    ~CustomComponent();

    virtual void awake();
    virtual void start();
    virtual void update(float deltaTime);
    virtual void render();
    };

```
<br>

2. Implement Constructor and Destructor: Implement the constructor and destructor for your custom component. Pass the GameObject* parameter to the base constructor. Adding additional parameters in the constructor is also possible.

```cpp
    #include "CustomComponent.h"

    namespace FumoEngine {

    CustomComponent::CustomComponent(GameObject* go) : BaseComponent(go) {
    // Custom initialization if needed
    }

    CustomComponent::~CustomComponent() {
    // Custom cleanup if needed
    }

    // Implement the rest of the component's methods...
    }
```
<br>

3. Define Custom Behavior: Inside your custom component class, implement the methods (awake(), start(), update(), render(), etc.) to define the behavior of your component. Customize these methods according to the functionality your component should provide.

```cpp
    void CustomComponent::awake() {
    // Initialize resources or perform actions upon awakening
    }

    void CustomComponent::start() {
    // Perform setup or initialization tasks when the component starts
    }

    void CustomComponent::update(float deltaTime) {
    // Implement component-specific update logic
    }

    void CustomComponent::render() {
    // Implement rendering logic if necessary
    }
```
<br>

4. Add Custom Component to GameObject: When creating a GameObject, you can attach your custom component to it. For example, if you want to add CustomComponent to a GameObject named myObject:

```cpp
    // Create a GameObject
    GameObject* myObject = new GameObject();

    // Attach CustomComponent to the GameObject
    myObject->addComponent<CustomComponent>();

    // Optionally, add more components if needed
    // myObject->addComponent(...);

    // Add the GameObject to the scene or perform other actions
```
<br>

5. Integrate Custom Component in the Game: After attaching your custom component to a GameObject, integrate it into your game logic. You can manipulate and interact with the component through the GameObject it's attached to.
<br>

### Notes:
    - Components can be added multiple times to the same game object by default, to disable this funcitonality, you can add the line 'allowMultiple = false' in either
    your header file or initialize(). It is a variable inherited from BaseComponent.
    - You can also inherit from your CustomComponent to create your own components with similar behaviours to its parent as seen in showcase sample game's EnemyCollider which inherits the core component of CircleCollider of Fumo Engine.

<hr><br>

## Tying scene and components {#tyingit}

You can tie both together by mostly:

    1. Create and design multiple scenes to represent different parts of your game.
    2. Populate scenes with game objects and customize their properties using their built-in functions.
    3. Attach and override appropriate components to game objects to give them behaviors.
    4. Add logic in the scene itself to manage the interactions and inputs of the scene.

<hr><br>

## Core Game Engine Components {#core-game-engine-components}

### TransformComponent {#transformcomponent}

The Transform Component, an essential part of the OCM system, handles transformations within the game. Key features of the Transform Component include:

1. Position Adjustments: Use the provided accessor methods to retrieve and modify the current position values of the GameObject.
```cpp
    void setXPosition(float value);
    void setYPosition(float value);
    void setPosition(float x, float y);
    void setPosition(Vector2 value);

    float getXPosition() const;
    float getYPosition() const;
    Vector2 getPosition() const;
```
<br>

2. Scale Adjustments: Use the provided accessor methods to retrieve and modify the current scale values of the GameObject.
```cpp
    void setXScale(float value);
    void setYScale(float value);
    void setScale(float x, float y);
    void setScale(Vector2 value);

    float getXScale() const;
    float getYScale() const;
    Vector2 getScale() const;
```
<br>

3. Rotation Adjustments: Use the provided accessor methods to retrieve and modify the current rotation values of the GameObject.
```cpp
    void setRotation(float value);
    float getRotation() const;

    void setVelocity(Vector2 value);
    Vector2 getVelocity() const;
```

<br>

4. Velocity Adjustments: Use the provided accessor methods to retrieve and modify the current velocity values of the GameObject. Velocity is an alternate way of setting constant movement for a game object. without having to run it inside the scene's update. This is done by just setting velocity and transform component itself will keep the object movement indefinitely.
```cpp
    void setVelocity(Vector2 value);
    Vector2 getVelocity() const;
```
<br>

### SpriteRenderer {#spriterenderer}

The SpriteRenderer component provides the following features:
Utilizes transform values from the Transform component.

1. Color tinting and opacity control. The default is white color with opacity of 1.0.
```cpp
    void setColor(float r, float g, float b);
    void setColor(Vector3 color);
    Vector3 getColor();

    void setOpacity(float a);
    float getOpacity();
```
<br>

2. Custom sprite size setting. The default is the loaded texture size.
```cpp
    void setSize(float w, float h);
    void setSize(Vector2 size);
    Vector2 getSize();
```
<br>

3. Sprite pivot adjustment. The default is (x:0.5, y:0.5).
```cpp
    void setPivot(float x, float y);
    void setPivot(Vector2 pivot);
    Vector2 getPivot();
```
<br>

### RendererComponent {#renderercomponent}

The renderer component is a simple component meant to render primitive shapes like Quad, Triangle and Circle. Despite its name, it is not the parent class of SpriteRenderer.

1. Color change and retrieval.
```cpp
    void setRGB(float r, float g, float b);
    Vector3 getRGB();
```
<br>

2. Set values when drawing a circle (Quad and Triangle doesn't have such settings due to not much need for it, they will use default values)
    - `circlePartition` : The amount of triangles needed to render the circle, 5 by default.
    - `circleRadius` : Radius of the circle, 5.0f by default.
```cpp
    void setCircleDrawValues(int circlePartition, float circleRadius);
```
<br>

3. Choose the shape to be rendered.
    - `ShapeToDraw` : Is an enum containing Quad, Triangle and Circle.
```cpp
    enum ShapeToDraw
    {
        Quad,
        Triangle,
        Circle
    };

    void setShapeToDraw(ShapeToDraw value);
```
<br>

### ProgressBar {#progressbar}
The ProgressBarComponent class offers functionality for creating and managing progress bars within the Fumo Engine environment:
Uses OpenGL to draw two quads: one for the background of the progress bar and another to indicate the current progress level. The position, size, and color of these rectangles are determined by the progress, barLength, and barHeight values, respectively.

1. Set colors with transparency for both the background and inner(progress) bar.
```cpp
    void setBackDropColor(float r, float g, float b, float a);
    Vector4 getBackDropColor();

    void setBarColor(float r, float g, float b, float a);
    Vector4 getBarColor();

    void setBothBarOpacity(float a);
```
<br>

2. Sets and gets the value of the progress bar. The default value is set to 0.5f, which is half full.
```cpp
    void setProgress(float value);
    float getProgress();
```
<br>

3. Set pivot for the bar similar to SpriteRenderer
```cpp
    void setPivot(float x, float y);
```
<br>

4. Set where the progress bar would extrude from, default is Left. This allows easy adaptation to both horizontal and vertical bars.
```cpp
    enum BarPivot
    {
        Top,
        Bottom,
        Left,
        Right,
        CenterHorizontal,
        CenterVertical
    };
    void setBarExtrudeFrom(BarPivot value);
```
<br>

5. Sets and gets the length of height of the entire bar itself (Both progress bar and backdrop). 
```cpp
    void setBarLength(float value);
    float getBarLength();
    void setBarHeight(float value);
    float getBarHeight();
```
<br>

### CircleCollider {#circlecollider}

The circle collider is a component that handles collision between different game objects with CircleCollider attached, it is a trigger collider as it does not
contain physics or solid collision. The collider also checks for UserTags to determine what object can be collided with, all GameObjects are given `Default`
tag at start.

1. Setting and getting the radius of the circle collider.
```cpp
    void setRadius(float rad);
    float getRadius() const;
```
<br>

2. Add, remove and get collidable UserTags. Each game object can only have one UserTag, you can however set the types of tags the collider can collide with.
```cpp
    //Defined in UserTags.h, can be added with more tags
    enum UserTag {
        Default,
        Player,
        Enemy,
        Bullet
    };

    void addCollidableTag(UserTag typeName);
    void removeCollidableTag(UserTag typeName);
    std::unordered_set<UserTag> getCollidableTags();
```
<br>

3. Manually check collision. This is already used to check collision by the circle collider itself, so there's no need to use this function unless you are specifically checking for collision with a specific object.
    - `containsPoint` : Check if a point is within the current circle collider.
    - `checkCircleCollision` : Check if the current collider is colliding with another specified collider
```cpp
    bool containsPoint(const Vector2& point) const;
    bool checkCircleCollision(const CircleCollider& other);
```
<br>

4. Overridable functions to implement custom logic when during, enter and exit collision.
    - These functions are meant to be overrided to provide your custom functionality, example can be seen in the sample game with EnemyCollider class in ShowCaseScene.cpp.
```cpp
    virtual void OnCollisionEnter(GameObject& other);
    virtual void OnCollisionExit(GameObject& other);
    virtual void OnCollisionStay(GameObject& other);


    //You can inherit the class and override the three specified functions like this
    class CustomCollider : public Fumo::CircleCollider {
    public:
        CustomCollider(Fumo::GameObject* go, float rad = 30.0f, bool isVisible = false) : CircleCollider(go, rad, isVisible) {}

        void OnCollisionEnter(Fumo::GameObject& other) override {
            //Your custom logic
        }
        void OnCollisionStay(Fumo::GameObject& other) override {
            //Your custom logic
        }
        void OnCollisionExit(Fumo::GameObject& other) override {
            //Your custom logic
        }
    };
```
<br>

5. Enable and disable collider render for debugging.
    - Method 1 : Enable when adding the component (Cannot be disabled during runtime).
    ```cpp
        //Second parameter is to enable the debug
        yourGameObject->addComponent<Fumo::CircleCollider>(radiusValue, true);
    ```
    <br>

    - Method 2 : Enable globally for all objects (Can be done during runtime).
    ```cpp
        Fumo::CircleCollider::globalShowCollider = true;
    ```
<br>

### Resource Management {#resource-management}

Resource allocation is managed through the ResourceAllocator class. This allows different kinds of resource allocators to exist without needing explicit code creation.
This allows different types of resources and allocated before they are displayed or called within the game screen, the current resource in the engine are textures only but the ResourceAllocator is capable of handling differnt types of resources.

1. Requesting Resource: To request a texture, call the `ResourceAllocator::allocateResource<Your_Resource_type>(path_string)`, this would return the specified resource instance of the given type.

4. Releasing Resource: When a texture is no longer needed, call `ResourceAllocator::releaseResource<Your_Resource_type>(path_string)`, this would do a check if said resource is shared amongst other game objects currently, if not it will unload the resource, if it is it would just reduce it's reference count.

5. Reference Counting: Each resource class maintains a reference count. Every time a resource is requested or reused, its reference count increases. When a resource is deleted, its reference count decreases. Resource with a reference count of zero are safe to be deleted.

6. Resource Management: The ResourceAllocator maintains an internal map of void pointers (void*) that stores loaded resource. This map allows for quick retrieval of existing resources and efficient management of memory.

<hr><br>

## Conclusion {#conclusion}

Thank you for attempting to use Fumo Engine! If you have any questions or issues do let me know on github or discord. Stay Funky.

## Acknowledgements {#acknowledgement}

External libraries used:
- glad by OpenGL
- glfw by OpenGL
- texture_utils.h provided by Mr. Faris
- angle_utils/vector provided by Mr. Faris
- angle_utils/matrix provided by Mr. Faris
- Doxygen for generating this document

Images:
- Fumo from Touhou Project
- Every other art asset is self-made