#include <imtui/imtui.h>
#include <imtui/imtui-impl-ncurses.h>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace ImGui;


constexpr float WIDTH = 71.0f;
constexpr float HEIGHT = 31.0f;
constexpr float RADIUS = 3;

class Ball {
private:
    float x, y;
    float vel_x, vel_y;
public:
    Ball() {
        x = rand() % (int)(WIDTH/2);
        y = rand() % (int)(HEIGHT/2);
        vel_x = rand() % 3 + 1;
        vel_y = rand() % 3 + 1;        
    }
    float getX() { return x;}
    
    // Function to update ball position and handle bouncing
    void update() {
        // Update position
        x += vel_x;
        y += vel_y;

        // Detect collision with horizontal left and right walls 
        if (x  <= RADIUS || x + RADIUS >= WIDTH - 1) {
            vel_x = -vel_x;
            x = (x <= RADIUS) ? RADIUS : WIDTH - RADIUS -1;
        }

        // Detect collision with top and bottom walls
        if (y <= RADIUS|| y + RADIUS >= HEIGHT) {
            vel_y = -vel_y;
            y = (y <= RADIUS) ? RADIUS : HEIGHT - RADIUS - 1;
        }
    }
    void draw(ImDrawList* draw_list, ImVec2 canvas_pos) {
        // compute the center according to the global coordinates
        ImVec2 ball_center = ImVec2(canvas_pos.x + x, 
                                    canvas_pos.y + y);

        draw_list->AddCircleFilled(ball_center, RADIUS, 
            IM_COL32(255, 255, 0, 255));
    }


};







// Render the game area. Returns true if we should exit
bool render_game(Ball &b) {
    SetNextWindowPos(ImVec2(2, 2), ImGuiCond_Once);
    SetNextWindowSize(ImVec2(WIDTH , HEIGHT + 10), ImGuiCond_Once);
    
    Begin("Bouncing Ball (Procedural - Circle)");
    
    // Get the draw list for custom drawing
    ImDrawList* draw_list = GetWindowDrawList();
    ImVec2 canvas_pos = GetCursorScreenPos();
    ImVec2 canvas_size = ImVec2(WIDTH, HEIGHT);
    
    
    b.draw(draw_list, canvas_pos);
    
    // Display info
    Text("Position: (%.1f, %.1f)", b.x, b.y);
    Text("Velocity: (%.1f, %.1f)", b.vel_x, b.vel_y);
    Text("Radius: %.1f", RADIUS);
    Text("Canvas Pos: %.1f %.1f", canvas_pos.x, canvas_pos.y);

    
    bool should_exit = false;
    if (Button("Exit")) {
        should_exit = true;
    }
    
    End();
    
    return should_exit;
}

int main() {
    srand(time(NULL));

    IMGUI_CHECKVERSION();
    CreateContext();

    auto screen = ImTui_ImplNcurses_Init(true);
    ImTui_ImplText_Init();

    //init_ball();
    Ball b;

    bool should_exit = false;
    while (!should_exit) {
        ImTui_ImplNcurses_NewFrame();
        ImTui_ImplText_NewFrame();

        NewFrame();

        b.update();
        
        should_exit = render_game(b);

        Render();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        ImTui_ImplText_RenderDrawData(GetDrawData(), screen);
        ImTui_ImplNcurses_DrawScreen();
    }

    ImTui_ImplText_Shutdown();
    ImTui_ImplNcurses_Shutdown();

    return 0;
}
