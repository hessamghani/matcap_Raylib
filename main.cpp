#include "raylib.h"
#include "rlgl.h" // for rlMatrix operations
#include "raymath.h"

int main(void) {
    // Initialization
    InitWindow(800, 600, "Shader Example with Normal Mapping");

    // Load model and texture
   // Model model = LoadModelFromMesh(GenMeshSphere(1.0f, 32, 32));  // sphere model
    Model model = LoadModel("matcap/monkey.obj");   // monkey model

    Texture2D texture = LoadTexture("matcap/bl.png");

    model.materials[0].maps[MATERIAL_MAP_ALBEDO].texture = texture;

    // Load shaderswa
    Shader shader = LoadShader("Matcap.vs", "Matcap.fs");

    // Get uniform locations
    int mvpLoc = GetShaderLocation(shader, "mvp");
    int normalMatrixLoc = GetShaderLocation(shader, "normalMatrix");

    // Assign shader to model
    model.materials[0].shader = shader;

    // Camera setup
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
 
    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {
    
        UpdateCamera(&camera,CAMERA_FREE); // Update camera


        float angle = GetTime() * 1.0f; // Rotate 30 degrees per second
        // Vector3 modelvec = (Vector3){ 0.0f, angle/150 , 0.0f };
        //model.transform = MatrixMultiply(model.transform, MatrixRotateY(0.02f));
        // Calculate matrices
        // Matrix modelMatrix = MatrixRotateXYZ(modelvec);
                Matrix modelMatrix = MatrixRotateXYZ((Vector3){ 0.0f, 0.0f, 0.0f });

        Matrix viewMatrix = MatrixLookAt(camera.position, camera.target, camera.up);
        Matrix projectionMatrix = MatrixPerspective(camera.fovy * DEG2RAD, 800.0f/600.0f, 0.1f, 100.0f);

        // MVP matrix
        Matrix mvpMatrix = MatrixMultiply(MatrixMultiply(projectionMatrix, viewMatrix), modelMatrix);
        SetShaderValueMatrix(shader, mvpLoc, mvpMatrix);

        // Normal matrix (inverse transpose of model-view matrix)
        Matrix normalMatrix = MatrixTranspose(MatrixInvert(MatrixMultiply(viewMatrix, modelMatrix)));
        SetShaderValueMatrix(shader, normalMatrixLoc, normalMatrix);




        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawModel(model, Vector3Zero(), 1.0f, WHITE);
       // DrawModelEx(model, (Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ 0.0f, 1.0f, 0.0f }, angle , (Vector3){ 1.0f, 1.0f, 1.0f }, WHITE);
       
        DrawGrid(10, 1.0f);
        EndMode3D();

        EndDrawing();
    }

    // De-Initialization
    UnloadModel(model);
    UnloadTexture(texture);
    UnloadShader(shader);

    CloseWindow();

    return 0;
}
