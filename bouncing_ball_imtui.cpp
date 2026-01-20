#include <imtui/imtui.h>
#include <imtui/imtui-impl-ncurses.h>
#include <string>

// Global variables for ball state
int ball_x = 0;
int ball_y = 0;
int ball_vel_x = 1;
int ball_vel_y = 1;

const int AREA_WIDTH = 40;
const int AREA_HEIGHT = 20;

// Function to initialize ball position
void init_ball() {
    ball_x = AREA_WIDTH / 2;
    ball_y = AREA_HEIGHT / 2;
    ball_vel_x = 1;
    ball_vel_y = 1;
}

// Function to update ball position and handle bouncing
void update_ball() {
    // Update position
    ball_x += ball_vel_x;
    ball_y += ball_vel_y;

    // Bounce off horizontal walls
    if (ball_x <= 0 || ball_x >= AREA_WIDTH - 1) {
        ball_vel_x = -ball_vel_x;
        ball_x = (ball_x <= 0) ? 0 : AREA_WIDTH - 1;
    }

    // Bounce off vertical walls
    if (ball_y <= 0 || ball_y >= AREA_HEIGHT - 1) {
        ball_vel_y = -ball_vel_y;
        ball_y = (ball_y <= 0) ? 0 : AREA_HEIGHT - 1;
    }
}

// Function to render the game area
// Returns true if we should exit
bool render_game() {
    ImGui::SetNextWindowPos(ImVec2(2, 2), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(AREA_WIDTH + 4, AREA_HEIGHT + 8), ImGuiCond_Once);
    
    ImGui::Begin("Bouncing Ball (Procedural)");
    
    // Render game area as text grid
    std::string game_area;
    for (int y = 0; y < AREA_HEIGHT; ++y) {
        for (int x = 0; x < AREA_WIDTH; ++x) {
            if (x == ball_x && y == ball_y) {
                game_area += '*';  // Ball
            } else if (x == 0 || x == AREA_WIDTH - 1 || y == 0 || y == AREA_HEIGHT - 1) {
                game_area += '|';  // Border
            } else {
                game_area += ' ';  // Empty space
            }
        }
        game_area += '\n';
    }
    
    ImGui::Text("%s", game_area.c_str());
    
    // Display info
    ImGui::Text("Position: (%d, %d)", ball_x, ball_y);
    ImGui::Text("Velocity: (%d, %d)", ball_vel_x, ball_vel_y);
    
    bool should_exit = false;
    if (ImGui::Button("Exit")) {
        should_exit = true;
    }
    
    ImGui::End();
    
    return should_exit;
}

int main() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    auto screen = ImTui_ImplNcurses_Init(true);
    ImTui_ImplText_Init();

    // Initialize ball
    init_ball();

    bool should_exit = false;
    while (!should_exit) {
        ImTui_ImplNcurses_NewFrame();
        ImTui_ImplText_NewFrame();

        ImGui::NewFrame();

        // Update ball
        update_ball();
        
        // Render game
        should_exit = render_game();

        ImGui::Render();

        ImTui_ImplText_RenderDrawData(ImGui::GetDrawData(), screen);
        ImTui_ImplNcurses_DrawScreen();
    }

    ImTui_ImplText_Shutdown();
    ImTui_ImplNcurses_Shutdown();

    return 0;
}
