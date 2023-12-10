#include "gui.hpp"
#include "../../Il2Cpp/CIl2Cpp.hpp"

// cba, to setup the project includes properly...
#include "framework/components/groupbox/groupbox.cpp"
#include "framework/components/window/window.cpp"
#include "framework/components/slider/slider.cpp"
#include "framework/components/keybind/keybind.cpp"
#include "framework/components/checkbox/checkbox.cpp"
#include "framework/components/colorpicker/colorpicker.cpp"
#include "framework/components/dropdown/dropdown.cpp"
#include "framework/components/textbox/textbox.cpp"
#include "framework/components/button/button.cpp"
#include "../../Includes/settings.hpp"
#include "../../Configs/Configs.hpp"

#include "../../Features/Visuals/Visuals.hpp"
#include "../../Includes/colorsettings.hpp"

auto reset_player_model()
{
    if (InGame)
    {
        AssemblyCSharp::PlayerModel().RebuildAll();
    }
}

namespace game {
    void create_game_object(uint64_t game_object, uint64_t unity_str) {
        const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GameObject")), XS("Internal_CreateGameObject"), 2));
        return reinterpret_cast<void(*)(uint64_t, uint64_t)>(_method)(game_object, unity_str);
    }

    void dont_destroy_object(uint64_t object) {
        const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("Object")), XS("DontDestroyOnLoad"), 1));
        return reinterpret_cast<void(*)(uint64_t)>(_method)(object);
    }

    uint64_t add_component(uint64_t game_object, uint64_t type_object) {
        const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GameObject")), XS("AddComponent"), 1));
        return reinterpret_cast<uint64_t(*)(uint64_t, uint64_t)>(_method)(game_object, type_object);
    }

    // engine drawing functions
    struct rect {
        float x, y, w, h;
    };

    /*
            struct drawing_prototypes_t {
            void( *line )( vec2_t start, vec2_t end, color_t color );
            void( *rect )( vec2_t position, vec2_t size, color_t color, float rounding );
            void( *filled_rect )( vec2_t position, vec2_t size, color_t color, float rounding );
            void( *text )( vec2_t position, const char* text, color_t color, int flags );
#ifdef CALLIOPE_USE_TEXT_SIZE
            vec2_t( *calc_text_size )( const char* text );
#endif
            void( *image )( vec2_t position, vec2_t size, void* source );
            void( *multi_color_filled_rect )( vec2_t position, vec2_t size, std::array<color_t, 4> colors );
            void( *push_clip_rect )( vec2_t mins, vec2_t maxs, bool allow_intersections );
            void( *pop_clip_rect )( );
            float( *get_frame_time )( );
        } drawing;
    */

    struct string
    {
        char zpad[0x10]{ };
        int size{ };
        wchar_t buffer[MAX_PATH];

        string(const wchar_t* st) : size((int)wcslen(st))
        {
            for (int idx = 0; idx < size; idx++)
            {
                buffer[idx] = st[idx];
            }
            buffer[size] = 0;
        }
    };

    struct color {
        float r, g, b, a;
    };

    struct vec2 {
        float x, y;
    };

    struct vec4 {
        float x, y, z, w;
    };

    namespace input {

        vec2 get_mouseScrollDelta()
        {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("Input")), XS("get_mouseScrollDelta"), 0));
            return reinterpret_cast<decltype(&get_mouseScrollDelta)>(_method)();
        }

    }

    namespace drawing {
        void rotate_around_pivot(float angle, vec2 pivot_point) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIUtility")), XS("RotateAroundPivot"), 2));
            return reinterpret_cast<decltype(&rotate_around_pivot)>(_method)(angle, pivot_point);
        }

        void draw_texture(rect r, uint64_t texture) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("DrawTexture"), 2));
            return reinterpret_cast<decltype(&draw_texture)>(_method)(r, texture);
        }

        void draw_texture_with_color_and_rounding(rect r, uint64_t texture, int scale_mode, bool alpha_blend, float image_aspect, color c, float border_width, float border_radius) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("DrawTexture"), 8));
            return reinterpret_cast<decltype(&draw_texture_with_color_and_rounding)>(_method)(r, texture, scale_mode, alpha_blend, image_aspect, c, border_width, border_radius);
        }

        void draw_texture_multi_colored(rect position, uint64_t image, int scaleMode, bool alphaBlend, float imageAspect, color leftColor, color topColor, color rightColor, color bottomColor, vec4 borderWidths, vec4 borderRadiuses, bool drawSmoothCorners) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("DrawTexture"), 12));
            return reinterpret_cast<decltype(&draw_texture_multi_colored)>(_method)(position, image, scaleMode, alphaBlend, imageAspect, leftColor, topColor, rightColor, bottomColor, borderWidths, borderRadiuses, drawSmoothCorners);
        }

        uint64_t get_white_texture() {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("Texture2D")), XS("get_whiteTexture"), 0));
            return reinterpret_cast<decltype(&get_white_texture)>(_method)();
        }

        uint64_t temp_content(game::string* str) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr_with_args(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIContent")), XS("Temp"), XS("t"), 1));
            return reinterpret_cast<decltype(&temp_content)>(_method)(str);
        }

        void set_gui_color(color c) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("set_color"), 1));
            return reinterpret_cast<decltype(&set_gui_color)>(_method)(c);
        }

        void set_font_size(uint64_t style, int size) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIStyle")), XS("set_fontSize"), 1));
            return reinterpret_cast<decltype(&set_font_size)>(_method)(style, size);
        }

        void set_alignment(uint64_t style, int text_anchor) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIStyle")), XS("set_alignment"), 1));
            return reinterpret_cast<decltype(&set_font_size)>(_method)(style, text_anchor);
        }

        void calc_text_size(uint64_t style, uint64_t content, vec2& out) {
            const static auto _method = CIl2Cpp::il2cpp_resolve_icall(XS("UnityEngine.GUIStyle::Internal_CalcSize_Injected"));
            return reinterpret_cast<decltype(&calc_text_size)>(_method)(style, content, out);
        }

        void label(rect position, uint64_t content, uint64_t style) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr_with_args(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("Label"), XS("content"), 3));
            return reinterpret_cast<decltype(&label)>(_method)(position, content, style);
        }

        uint64_t get_label(uint64_t skin) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUISkin")), XS("get_label"), 0));
            return reinterpret_cast<decltype(&get_label)>(_method)(skin);
        }

        uint64_t get_gui_skin() {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUI")), XS("get_skin"), 0));
            return reinterpret_cast<decltype(&get_gui_skin)>(_method)();
        }

        void gui_clip_push(rect r, vec2 scroll_offset, vec2 render_offset, bool reset_offset) {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIClip")), XS("Internal_Push"), 4));
            return reinterpret_cast<decltype(&gui_clip_push)>(_method)(r, scroll_offset, render_offset, reset_offset);
        }

        void gui_clip_pop() {
            const static auto _method = *reinterpret_cast<uint64_t*>(CIl2Cpp::get_method_ptr(CIl2Cpp::get_class(XS("UnityEngine"), XS("GUIClip")), XS("Internal_Pop"), 0));
            return reinterpret_cast<decltype(&gui_clip_pop)>(_method)();
        }
    }
}



void filled_rect(calliope::vec2_t position, calliope::vec2_t size, calliope::color_t color, float rounding = 0.f) {
    game::drawing::draw_texture_with_color_and_rounding({ position.x, position.y, size.x, size.y }, white_texture, 0, true, 0.f, *(game::color*)(&color), 0.f, rounding);
}

// you might have to modify this to fix rounding if you care about that...
void rect(calliope::vec2_t position, calliope::vec2_t size, calliope::color_t color, float rounding = 0.f)
{
    filled_rect(position, calliope::vec2_t(1, size.y), color, rounding);
    filled_rect(calliope::vec2_t(position.x + size.x, position.y), calliope::vec2_t(1, size.y), color, rounding);
    filled_rect(position, calliope::vec2_t(size.x, 1), color, rounding);
    filled_rect(calliope::vec2_t(position.x, position.y + size.y), calliope::vec2_t(size.x, 1), color, rounding);
}

// you will need to modify this to fix gradients...
// Import the Unity GL class from here, etc... 
// Or write your gradients another way... 
// you need to use GL.Viewport if you are going to use GL since it is not effected by GUIClip's.
// https://github.com/clxxe/sapphire/blob/main/sapphire/unity_gl.hpp#L85

void multi_color_filled_rect(calliope::vec2_t position, calliope::vec2_t size, std::array<calliope::color_t, 4> colors) {
    game::drawing::draw_texture_multi_colored({ position.x, position.y, size.x, size.y }, white_texture, 0, true, 0.f, { colors[0].r, colors[0].g, colors[0].b, colors[0].a },
        { colors[1].r, colors[1].g, colors[1].b, colors[1].a },
        { colors[2].r, colors[2].g, colors[2].b, colors[2].a },
        { colors[3].r, colors[3].g, colors[3].b, colors[3].a }, { 0.f, 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f, 0.f }, false);
}

// You will also want to include, https://docs.unity3d.com/ScriptReference/GL.Viewport.html

void push_clip_rect(calliope::vec2_t mins, calliope::vec2_t maxs, bool allow_intersections) {
    game::drawing::gui_clip_push({ mins.x, mins.y, maxs.x, maxs.y }, { 0.f, 0.f }, { 0.f, 0.f }, true);
}

void pop_clip_rect() {
    game::drawing::gui_clip_pop();
}

size_t custom_mbstowcs(wchar_t* dest, const char* src, size_t destsz) {
    if (dest == nullptr || src == nullptr) {
        return static_cast<size_t>(-1); // Invalid argument
    }

    size_t i = 0;
    while (i < destsz - 1 && src[i] != '\0') {
        dest[i] = static_cast<wchar_t>(src[i]);
        i++;
    }

    dest[i] = L'\0';

    if (i == destsz - 1 && src[i] != '\0') {
        dest[0] = L'\0';
        return static_cast<size_t>(-1); // Insufficient space in the destination buffer
    }

    return i; // Number of characters converted
}

calliope::vec2_t calc_text_size(const char* text) {
    game::vec2 text_size{ 0, 0 };

    wchar_t buf[MAX_PATH]{ };
    custom_mbstowcs(buf, text, sizeof(buf));

    auto _strbuf = game::string(buf);
    auto content = game::drawing::temp_content(&_strbuf);

    game::drawing::calc_text_size(label_style, content, text_size);

    return { text_size.x, text_size.y };
}

void text(calliope::vec2_t position, const char* text, calliope::color_t color, int flags) {
    if (!label_style)
        return;

    wchar_t buf[MAX_PATH]{ };
    custom_mbstowcs(buf, text, sizeof(buf));

    auto _strbuf = game::string(buf);
    auto content = game::drawing::temp_content(&_strbuf);

    game::vec2 text_size{ 0, 0 };
    game::drawing::calc_text_size(label_style, content, text_size);

    if (flags & calliope::menu_t::text_flags::text_flags_style_outline) {
        game::drawing::set_gui_color({ 0.f, 0.f, 0.f, color.a });
        game::drawing::label({ position.x + 1, position.y + 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x - 1, position.y - 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x + 1, position.y - 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x - 1, position.y + 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x + 1, position.y, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x - 1, position.y, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x, position.y - 1, text_size.x, text_size.y }, content, label_style);
        game::drawing::label({ position.x, position.y + 1, text_size.x, text_size.y }, content, label_style);
    }

    if (flags & calliope::menu_t::text_flags::text_flags_style_dropshadow) {
        game::drawing::set_gui_color({ 0.f, 0.f, 0.f, color.a });
        game::drawing::label({ position.x + 1, position.y + 1, text_size.x, text_size.y }, content, label_style);
    }

    game::drawing::set_gui_color({ color.r, color.g, color.b, color.a });
    game::drawing::label({ position.x, position.y, text_size.x, text_size.y }, content, label_style);
}

int calliope::globals::menu_alpha = 255;
calliope::color_t calliope::globals::menu_accent(255, 255, 255, 255);

bool tracking_prediction;

void GUI::SetupGUI()
{
    static bool do_once = false;

    if (!do_once)
    {
        calliope::menu.drawing.calc_text_size = calc_text_size;
        calliope::menu.drawing.filled_rect = filled_rect;
        calliope::menu.drawing.rect = rect;
        calliope::menu.drawing.text = text;
        calliope::menu.drawing.multi_color_filled_rect = multi_color_filled_rect;
        //calliope::menu.drawing.image = image;
        calliope::menu.drawing.push_clip_rect = push_clip_rect;
        calliope::menu.drawing.pop_clip_rect = pop_clip_rect;

        do_once = true;
    }


    if (!white_texture)
        white_texture = (uint64_t)UnityEngine::Texture2D::get_whiteTexture();

    if (!skin || !label_style) {
        skin = (uint64_t)UnityEngine::GUI::GetSkin();
        label_style = (uint64_t)reinterpret_cast<UnityEngine::GUISkin*>(skin)->m_label();
    }

    game::drawing::set_font_size(label_style, 11);
    game::drawing::set_alignment(label_style, 4);

    // game::drawing::draw_texture_with_color_and_rounding({ 10, 10, 50, 50 }, white_texture, 0, true, 0.f, { 1.f, 0.f, 0.f, 1.f }, 0.f, 4.f);

    // game::drawing::draw_texture_multi_colored({ 10, 10, 200, 200 }, white_texture, 0, true, 0.f, { 1.f, 0.f, 0.f, 0.5f }, { 0.f, 1.f, 0.f, 0.5f }, { 0.f, 0.f, 1.f, 0.5f }, { 1.f, 1.f, 0.f, 0.5f }, game::vec4(0, 0, 0, 0), game::vec4(0, 0, 0, 0.f), false);

     // you may want to change this to use the Unity VK Keys instead, etc... unity mouse buttons its all up to your preferences...
    calliope::util::get_key_states();

    // replace this with... https://docs.unity3d.com/ScriptReference/Input-mouseScrollDelta.html
    calliope::menu.mouse_wheel_delta
        = game::input::get_mouseScrollDelta().y * 0.1f;
}
std::string nigga = "";
int keybd = 0;
int groupbox_sz = 250;
int groupbox_sz_y = 360;

int full_groupbox_sz = 510;

int small_aimbot_tab_y = 115;
int small_visuals_tab_y = 180;

int small_rage_tab_y = 185;
int small_rage_tab2_y = 170;

int small_player_tab_y = 165;
int small_box_tab_y = 80;

int small_otherplayer_tab_y = 165;
int small_invetory_tab = 80;

int small_chams_tab = 250;
int small_chams_minitab = 80;

int smaller_world_tab = 95;
int small_world_tab = 105;
int small_world_tab2 = 125;
int small_world_tab3 = 155;

int small_deployable_tab = 150;
int small_deplayable_tab2 = 120;

int small_home_tab = 220;

int small_traps_tab = 155;
int small_traps_tab2 = 120;

int small_flyhack_tab = 100;
int small_misc_tab = 140;
int small_instant_tab = 80;
int small_collision_tab = 80;

int small_auto_tab = 145;
int small_spam_tab = 190;
int small_prefab_tab = 90;

int small_weapons_tab = 260;
int small_weapon_tab2 = 90;

int small_loadeffects_tab = 80;

int small_bright_tab = 110;
int small_sky_tab = 110;

int small_nosky_tab = 150;
int small_weather_tab = 80;

int small_text_tab = 230;
int small_config_tab = 160;

int testvalue = 0;

void AimbotTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Aimbot"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_aimbot_tab_y))) {
        calliope::menu.components.checkbox(XS("Silent-Aim"), m_settings::SilentAim);
        calliope::menu.components.keybind(XS("SilentAim Key"), (int&)m_settings::AimbotKey, true);
        if (m_settings::SilentAim)
            m_settings::RotationAimbot = false;
        calliope::menu.components.checkbox(XS("Legit-Silent"), m_settings::RotationAimbot);
        calliope::menu.components.checkbox(XS("Melee-SilentAim"), m_settings::MeleeAimbot);
        calliope::menu.components.checkbox(XS("Silent-Melee"), m_settings::SilentMelee);
 
        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Aimbot Settings"), calliope::vec2_t(50, 10 + small_aimbot_tab_y), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_aimbot_tab_y - 25))) {

        calliope::menu.components.checkbox(XS("Target-NPC"), m_settings::AimbotNPC);
        calliope::menu.components.checkbox(XS("Target-Wounded"), m_settings::TargetWounded);

        calliope::menu.components.dropdown(XS("Aimbone"), { ("Head"), ("Neck"), ("Chest"), ("Random")/*, ("Closest To Crosshair")*/ }, m_settings::SelectedAimbone);

        calliope::menu.components.slider<float>(XS("Accuracy"), XS(""), m_settings::AimbotAccuracy, 0, 100);
        calliope::menu.components.slider<float>(XS("Fov-Slider"), XS(""), m_settings::AimbotFOV, 0, 1000);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_three = calliope::menu.components.groupbox(XS("Aimbot Visuals"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, small_visuals_tab_y))) {

        calliope::menu.components.colorpicker(XS("Crosshair Color"), ColorSettings::Crosshair_Color, true);
        calliope::menu.components.checkbox(XS("Crosshair"), m_settings::Crosshair);

        calliope::menu.components.colorpicker(XS("FOV Color"), ColorSettings::FOV_Color, true);
        calliope::menu.components.checkbox(XS("FOV-Circle"), m_settings::DrawFov);

        calliope::menu.components.colorpicker(XS("TargetSnapline Color"), ColorSettings::TargetSnapline_Color, true);
        calliope::menu.components.checkbox(XS("Target-Snapline"), m_settings::Aimline);

        calliope::menu.components.colorpicker(XS("TargetMarker Color"), ColorSettings::TargetMarker_Color, true);
        calliope::menu.components.checkbox(XS("Target-Marker"), m_settings::AimMarker);

        // calliope::menu.components.checkbox(XS("Target Indicator"), m_settings::Target_Indicator);
        calliope::menu.components.colorpicker(XS("BulletTracers Color"), ColorSettings::BulletTracers_Color, true);
        calliope::menu.components.checkbox(XS("Bullet-Tracers"), m_settings::BulletTracers);

        calliope::menu.components.dropdown(XS("Hit-Material"), { ("Flesh"), ("Glass"), ("Metal"), ("Water") }, m_settings::HitMaterial);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_four = calliope::menu.components.groupbox(XS("Other"), calliope::vec2_t(60 + groupbox_sz, 10 + small_visuals_tab_y), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_visuals_tab_y - 25))) {

        calliope::menu.components.checkbox(XS("Hitbox-Override"), m_settings::HitboxOverride);

        if (m_settings::HitboxOverride)
        {
            calliope::menu.components.dropdown(XS("HitBox"), { ("Head"), ("Chest"), ("Random") }, m_settings::SelectedHitbox);
        }

        calliope::menu.components.checkbox(XS("Auto-Reload"), m_settings::AutoReload);
        if (m_settings::AutoReload)
        {
            calliope::menu.components.checkbox(XS("Auto-Reload-Icon"), m_settings::AutoReloadIcon);
        }

        calliope::menu.components.end_groupbox();
    }

}

void RageTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Manipulation"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_rage_tab2_y))) {


        calliope::menu.components.checkbox(XS("Manipulation"), m_settings::Manipulation, { ("To save FPS, enable Simulate-Angles") });
        calliope::menu.components.keybind(XS("Manipulation Key"), (int&)m_settings::ManipKey, true);

        calliope::menu.components.checkbox(XS("Manip-Indicator"), m_settings::ManipFlags);
        calliope::menu.components.checkbox(XS("Manip-Point"), m_settings::DrawManipPoints);
        calliope::menu.components.slider<float>(XS("Manip-Scanning-Speed"), XS(""), m_settings::ManipPoints, 0, 50, { ("Please keep this low unless you have a god-pc, this will use FPS") });
        calliope::menu.components.dropdown(XS("Manip-Mode"), { ("Static Points"), ("Dynamic Points"), ("Enhanced Points") }, m_settings::ManipMode);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Simulation"), calliope::vec2_t(50, 10 + small_rage_tab2_y), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_rage_tab2_y - 25))) {

        calliope::menu.components.checkbox(XS("Simulate-Angles (Saves FPS)"), m_settings::CacheBulletTP);
        calliope::menu.components.checkbox(XS("Behind-Wall (FPS)"), m_settings::BehindWall);
        if (m_settings::CacheBulletTP)
        {
            //calliope::menu.components.checkbox(XS("AdvancedCaching (Saves FPS)"), m_settings::AdvancedChecks);
            m_settings::AdvancedChecks = true;
        }
        else
            m_settings::AdvancedChecks = false;

        // calliope::menu.components.checkbox(XS("Simulated-Indicator"), m_settings::ShowCachedLOS);
        calliope::menu.components.checkbox(XS("Simulated-Point"), m_settings::ShowCachedPoint);
        calliope::menu.components.slider<float>(XS("Simulated-Points"), XS(""), m_settings::LOSCheckAmount, 0, 2000);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_three = calliope::menu.components.groupbox(XS("BulletTP"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, small_rage_tab_y))) {

        calliope::menu.components.checkbox(XS("BulletTP"), m_settings::BulletTP, { ("To save FPS, enable Simulate-Angles") });
        calliope::menu.components.checkbox(XS("BulletTP-Indicator"), m_settings::BulletTPFlags);
        calliope::menu.components.checkbox(XS("BulletTP-Arrows"), m_settings::Thickbullet_Arrows);
        calliope::menu.components.checkbox(XS("BulletTP-Angle"), m_settings::ShowBulletTPAngle);
        calliope::menu.components.checkbox(XS("Snicker-Lines"), m_settings::SnickerBullet);
        calliope::menu.components.checkbox(XS("Shot-Indicators"), m_settings::ShotIndicators, {"Shows when a shot hits/miss on the notifications"});

        calliope::menu.components.dropdown(XS("BulletTP Mode"), { ("Static Angles"), ("Dynamic Angles"), ("Enhanced Angles") }, m_settings::BulletTPIntensity);


        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_four = calliope::menu.components.groupbox(XS("Settings"), calliope::vec2_t(60 + groupbox_sz, 10 + small_rage_tab_y), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_rage_tab_y - 25))) {

        calliope::menu.components.checkbox(XS("AutoShoot"), m_settings::Autoshoot);
        if (m_settings::Autoshoot)
        {
            calliope::menu.components.keybind(XS("AutoShoot Bind"), (int&)m_settings::AutoshootKey, true);
        }
        calliope::menu.components.checkbox(XS("Auto-Stop"), m_settings::StopPlayer);
        calliope::menu.components.checkbox(XS("Pierce-Materials"), m_settings::PierceMaterials);
        calliope::menu.components.checkbox(XS("Bullet-Queue"), m_settings::InstantKill);
        calliope::menu.components.checkbox(XS("Instant-Hit"), m_settings::InstantBullet);
        calliope::menu.components.checkbox(XS("Wait-For-Instant-Hit/Queue"), m_settings::WaitForInstantHit);


        calliope::menu.components.end_groupbox();
    }

}

void PlayersVisuals()
{

    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Player"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_player_tab_y))) {

        calliope::menu.components.colorpicker(XS("Username Color"), ColorSettings::Username_Color, true);
        calliope::menu.components.checkbox(XS("Username"), m_settings::nameEsp);

        calliope::menu.components.colorpicker(XS("HeldItem Color"), ColorSettings::Helditem_Color, true);
        calliope::menu.components.checkbox(XS("HeldItem"), m_settings::helditem);

        //if (m_settings::helditem)
        //{
        //    calliope::menu.components.dropdown(XS("HeldItemType"), { ("Text"), ("Unity Icon"), ("Custom Icon") }, m_settings::HeldItemType);
        //}

      //  calliope::menu.components.checkbox(XS("HeldItemIcon"), m_settings::HeldItemIcon);

        calliope::menu.components.colorpicker(XS("Box Color"), ColorSettings::BoxEsp_Color, true);
        calliope::menu.components.checkbox(XS("Box"), m_settings::BoxEsp);
        {
            if (m_settings::BoxEsp) {
                m_settings::SelectedBoxESP = 1;
                m_settings::CornerBox = false;
            }
        }
        calliope::menu.components.checkbox(XS("Corner-Box"), m_settings::CornerBox);
        {
            if (m_settings::CornerBox) {
                m_settings::SelectedBoxESP = 2;
                m_settings::BoxEsp = false;
            }
            if (!m_settings::BoxEsp && !m_settings::CornerBox)
                m_settings::SelectedBoxESP = 0;
        }

        // calliope::menu.components.colorpicker(XS("Skeleton Color"), ColorSettings::FOV_Color, true);
        calliope::menu.components.checkbox(XS("Skeleton"), m_settings::Skeleton);

        calliope::menu.components.dropdown(XS("Vischeck"), { ("None"), ("Enabled"), ("Tags Enabled"), ("Both") }, m_settings::VisCheckType);

        if (m_settings::VisCheckType == 0) {
            m_settings::EspVisCheck = false;
            m_settings::TagsVisCheck = false;
        }
        else if (m_settings::VisCheckType == 1) {
            m_settings::EspVisCheck = true;
            m_settings::TagsVisCheck = false;
        }
        else if (m_settings::VisCheckType == 2) {
            m_settings::EspVisCheck = false;
            m_settings::TagsVisCheck = true;
        }
        else if (m_settings::VisCheckType == 3) {
            m_settings::EspVisCheck = true;
            m_settings::TagsVisCheck = true;
        }

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx_2 = calliope::menu.components.groupbox(XS("HealthBar"), calliope::vec2_t(50, 10 + small_player_tab_y), calliope::vec2_t(groupbox_sz / 2, small_box_tab_y))) {

        calliope::menu.components.checkbox(XS("Bottom-bar"), m_settings::bottomhealthbar);
        if (m_settings::bottomhealthbar) {
            m_settings::lefthealthbar = false;
            m_settings::SelectedHealthBar = 1;
        }
        calliope::menu.components.checkbox(XS("Left-bar"), m_settings::lefthealthbar);
        if (m_settings::lefthealthbar) {
            m_settings::bottomhealthbar = false;
            m_settings::SelectedHealthBar = 2;
        }

        if (!m_settings::bottomhealthbar && !m_settings::lefthealthbar)
            m_settings::SelectedHealthBar = 0;

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx_3 = calliope::menu.components.groupbox(XS("BaseCheck"), calliope::vec2_t(50 + (groupbox_sz / 2), 10 + small_player_tab_y), calliope::vec2_t(groupbox_sz / 2, small_box_tab_y))) {
        calliope::menu.components.colorpicker(XS("Outside Color"), ColorSettings::Outside_Color, true);
        calliope::menu.components.checkbox(XS("Outside"), m_settings::ShowOutside);

        calliope::menu.components.colorpicker(XS("Inside Color"), ColorSettings::Inside_Color, true);
        calliope::menu.components.checkbox(XS("Inside"), m_settings::ShowInside);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx_3 = calliope::menu.components.groupbox(XS("Radar"), calliope::vec2_t(50, 10 + small_player_tab_y + 10 + small_box_tab_y), calliope::vec2_t(groupbox_sz, small_box_tab_y))) {
        calliope::menu.components.checkbox(XS("Radar"), m_settings::Radar);
        calliope::menu.components.slider<float>(XS("Radar-Size"), XS(""), m_settings::RadarSize, 0, 300);

        calliope::menu.components.end_groupbox();
    }


    if (auto groupbox_ctx_p1 = calliope::menu.components.groupbox(XS("Player Settings"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, small_otherplayer_tab_y))) {

        calliope::menu.components.colorpicker(XS("Wounded Color"), ColorSettings::Wounded_Color, true);
        calliope::menu.components.checkbox(XS("Wounded"), m_settings::DrawWounded);

        calliope::menu.components.colorpicker(XS("Safezone Color"), ColorSettings::Safezone_Color, true);
        calliope::menu.components.checkbox(XS("Safezone"), m_settings::DrawSafezone);

        calliope::menu.components.colorpicker(XS("Npc Color"), ColorSettings::NPC_Color, true);
        calliope::menu.components.checkbox(XS("Npc's"), m_settings::DrawNPC);

        calliope::menu.components.colorpicker(XS("Sleepers Color"), ColorSettings::Sleeper_Color, true);
        calliope::menu.components.checkbox(XS("Sleepers"), m_settings::DrawSleepers);

        calliope::menu.components.slider<float>(XS("Player Distance"), XS(""), m_settings::PlayerESPDistance, 0, 500);
        calliope::menu.components.slider<float>(XS("NPC Distance"), XS(""), m_settings::NPCDistance, 0, 500);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx_p2 = calliope::menu.components.groupbox(XS("Inventory"), calliope::vec2_t(60 + groupbox_sz, 10 + small_otherplayer_tab_y), calliope::vec2_t(groupbox_sz / 2, small_invetory_tab))) {

        calliope::menu.components.checkbox(XS("IText"), m_settings::InventoryText);
        if (m_settings::InventoryText)
            m_settings::SelectedHotbar = 1;
        calliope::menu.components.checkbox(XS("IIcons"), m_settings::InventoryIcons);
        if (m_settings::InventoryIcons)
            m_settings::SelectedHotbar = 2;

        if (!m_settings::InventoryText && !m_settings::InventoryIcons)
            m_settings::SelectedHotbar = 0;

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx_p3 = calliope::menu.components.groupbox(XS("Clothing"), calliope::vec2_t(60 + groupbox_sz + (groupbox_sz / 2), 10 + small_otherplayer_tab_y), calliope::vec2_t(groupbox_sz / 2, small_invetory_tab))) {

        calliope::menu.components.checkbox(XS("CText"), m_settings::ClothingText);
        if (m_settings::ClothingText)
            m_settings::SelectedClothing = 1;
        calliope::menu.components.checkbox(XS("CIcons"), m_settings::ClothingIcons);
        if (m_settings::ClothingIcons)
            m_settings::SelectedClothing = 2;

        if (!m_settings::ClothingText && !m_settings::ClothingIcons)
            m_settings::SelectedClothing = 0;

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx_p3 = calliope::menu.components.groupbox(XS("Misc"), calliope::vec2_t(60 + groupbox_sz, 10 + small_otherplayer_tab_y + 10 + small_invetory_tab), calliope::vec2_t(groupbox_sz, small_invetory_tab))) {

        calliope::menu.components.checkbox(XS("Show-Alerts"), m_settings::ShowAlerts);
        calliope::menu.components.colorpicker(XS("ShowTargetESP Color"), ColorSettings::Target_Color, true);
        calliope::menu.components.checkbox(XS("Show-Target"), m_settings::DrawTarget);
        calliope::menu.components.colorpicker(XS("Visible Color"), ColorSettings::Visible_Color, false);

        calliope::menu.components.end_groupbox();
    }


}

void ChamsTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("PlayerChams"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_chams_tab))) {

        calliope::menu.components.checkbox(XS("Player-Chams"), m_settings::PlayerChams);
        calliope::menu.components.dropdown(XS("PChams-Type"), { ("None"), ("NightFire Blue"), ("NightFire Red"), ("Lightning"), ("Geometric Disolve"), ("Galaxy"), ("WireFrame"), ("Color"), ("RPBGalaxy"), ("Glitter") }, m_settings::SelectedChams);

        if (m_settings::SelectedChams == 7)
        {
            calliope::menu.components.colorpicker(XS("CVisible-Color"), ColorSettings::VisibleChams_Color, false);
            calliope::menu.components.colorpicker(XS("CInvisible-Color"), ColorSettings::InvisibleChams_Color, false);
            calliope::menu.components.colorpicker(XS("CScientist-Color"), ColorSettings::ScientistChams_Color, false);
        }

        if (m_settings::SelectedChams == 9)
        {
            calliope::menu.components.colorpicker(XS("Glitter-Color"), ColorSettings::GChams_GlitterColor, false);
        }

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx_2 = calliope::menu.components.groupbox(XS("Load Chams"), calliope::vec2_t(50, 10 + small_chams_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_chams_tab - 25))) {

        calliope::menu.components.checkbox(XS("Load-Galaxy"), m_settings::LoadGalaxy);
        calliope::menu.components.checkbox(XS("Load-RPBGalaxy"), m_settings::LoadRBP);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Weapon Chams"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, groupbox_sz_y - 10))) {
        calliope::menu.components.checkbox(XS("Weapon-Chams"), m_settings::WeaponChams);
        calliope::menu.components.checkbox(XS("Ignore-Arms"), m_settings::IgnoreArms);
        calliope::menu.components.dropdown(XS("WChams-Type"), { ("NightFire Blue"), ("NightFire Red"), ("Lightning"), ("Geometric Disolve"), ("Galaxy"), ("WireFrame"), ("RPBGalaxy"), ("Glitter"), ("Damascus") }, m_settings::WeaponSelectedChams);

        if (m_settings::WeaponSelectedChams == 0)
        {
            calliope::menu.components.colorpicker(XS("BFlame1-Color"), ColorSettings::GChams_BlueFlameColor1, false);
            calliope::menu.components.colorpicker(XS("BFlame2-Color"), ColorSettings::GChams_BlueFlameColor2, false);
        }
        if (m_settings::WeaponSelectedChams == 1)
        {
            calliope::menu.components.colorpicker(XS("RFlame1-Color"), ColorSettings::GChams_RedFlameColor1, false);
            calliope::menu.components.colorpicker(XS("RFlame2-Color"), ColorSettings::GChams_RedFlameColor2, false);
        }
        //if (m_settings::WeaponSelectedChams == 3)
        //{
        //    calliope::menu.components.colorpicker(XS("Lightning-Color"), ColorSettings::GChams_LightningColor, false);
        //}
        if (m_settings::WeaponSelectedChams == 7)
        {
            calliope::menu.components.colorpicker(XS("Glitter-Color"), ColorSettings::GChams_GlitterColor, false);
        }

        if (m_settings::WeaponSelectedChams == 8)
        {
            calliope::menu.components.colorpicker(XS("DTop-Color"), ColorSettings::GChams_DamascusColor2, false);
            calliope::menu.components.colorpicker(XS("DBottom-Color"), ColorSettings::GChams_DamascusColor1, false);
            calliope::menu.components.colorpicker(XS("DGradient-Color"), ColorSettings::GChams_DamascusGradient1, false);
            calliope::menu.components.colorpicker(XS("Pattern-Color"), ColorSettings::GChams_DamascusPattern1, false);
            calliope::menu.components.slider<float>(XS("DGradient-Pos"), XS(""), m_settings::DGradientPos, -1, 1);
            calliope::menu.components.slider<float>(XS("DGradient-Strength"), XS(""), m_settings::DGradientSpread, 0, 1);
        }

        calliope::menu.components.end_groupbox();
    }

}

int WorldPage = 0;
int WorldStartSize = 30;
void WorldTab()
{
    calliope::menu.components.sidecombo(XS("Page"), { "Page 1", "Page 2", "Page 3", "Page 4" }, WorldPage, calliope::vec2_t(50, 0), calliope::vec2_t(full_groupbox_sz, 20));

    if (WorldPage == 0) {
        if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("PlayerDrops"), calliope::vec2_t(50, WorldStartSize), calliope::vec2_t(groupbox_sz, small_world_tab))) {
            calliope::menu.components.colorpicker(XS("Corpse Color"), ColorSettings::Corpse_Color, true);
            calliope::menu.components.checkbox(XS("Corpse"), m_settings::Corpse);

            calliope::menu.components.colorpicker(XS("Backpack Color"), ColorSettings::Backpack_Color, true);
            calliope::menu.components.checkbox(XS("Backpack"), m_settings::BackPack);

            calliope::menu.components.slider<float>(XS("Drops Distance"), XS(""), m_settings::MaxPlayerDropsDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_ctx_2 = calliope::menu.components.groupbox(XS("Ores"), calliope::vec2_t(50, WorldStartSize + 10 + small_world_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_world_tab2 - WorldStartSize - 5))) {

            calliope::menu.components.colorpicker(XS("StoneOre Color"), ColorSettings::StoneOre_Color, true);
            calliope::menu.components.checkbox(XS("Stone"), m_settings::StoneOre);

            calliope::menu.components.colorpicker(XS("MetalOre Color"), ColorSettings::MetalOre_Color, true);
            calliope::menu.components.checkbox(XS("Metal"), m_settings::MetalOre);

            calliope::menu.components.colorpicker(XS("SulfurOre Color"), ColorSettings::SulfurOre_Color, true);
            calliope::menu.components.checkbox(XS("Sulfur"), m_settings::SulfurOre);

            calliope::menu.components.slider<float>(XS("Ore Distance"), XS(""), m_settings::MaxOreDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_two = calliope::menu.components.groupbox(XS("Collectables"), calliope::vec2_t(60 + groupbox_sz, WorldStartSize), calliope::vec2_t(groupbox_sz, small_world_tab3))) {

            calliope::menu.components.colorpicker(XS("Hemp Color"), ColorSettings::Hemp_Color, true);
            calliope::menu.components.checkbox(XS("Hemp"), m_settings::Hemp);

            calliope::menu.components.colorpicker(XS("DieselBarrel Color"), ColorSettings::DieselBarrel_Color, true);
            calliope::menu.components.checkbox(XS("Diesel-Barrel"), m_settings::DieselBarrel);

            calliope::menu.components.colorpicker(XS("StoneCollectable Color"), ColorSettings::StoneCollectable_Color, true);
            calliope::menu.components.checkbox(XS("Stone-Collectable"), m_settings::StoneCollectable);

            calliope::menu.components.colorpicker(XS("MetalCollectable Color"), ColorSettings::MetalCollectable_Color, true);
            calliope::menu.components.checkbox(XS("Metal-Collectable"), m_settings::MetalCollectable);

            calliope::menu.components.colorpicker(XS("SulfurCollectable Color"), ColorSettings::SulfurCollectable_Color, true);
            calliope::menu.components.checkbox(XS("Sulfur-Collectable"), m_settings::SulfurCollectable);

            calliope::menu.components.slider<float>(XS("Collectables Distance"), XS(""), m_settings::MaxCollectableDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_two = calliope::menu.components.groupbox(XS("Food"), calliope::vec2_t(60 + groupbox_sz, WorldStartSize + 10 + small_world_tab3), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_world_tab3 - 25 - WorldStartSize))) {

            calliope::menu.components.colorpicker(XS("Corn Color"), ColorSettings::Corn_Color, true);
            calliope::menu.components.checkbox(XS("Corn"), m_settings::Corn);

            calliope::menu.components.colorpicker(XS("Pumpkin Color"), ColorSettings::Pumpkin_Color, true);
            calliope::menu.components.checkbox(XS("Pumpkin"), m_settings::Pumpkin);

            calliope::menu.components.colorpicker(XS("Potato Color"), ColorSettings::Potato_Color, true);
            calliope::menu.components.checkbox(XS("Potato"), m_settings::Potato);

            calliope::menu.components.colorpicker(XS("Mushroom Color"), ColorSettings::Mushroom_Color, true);
            calliope::menu.components.checkbox(XS("Mushroom"), m_settings::Mushroom);

            calliope::menu.components.slider<float>(XS("Food Distance"), XS(""), m_settings::MaxFoodDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }
    }
    else if (WorldPage == 1)
    {
        if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Deployables"), calliope::vec2_t(50, WorldStartSize), calliope::vec2_t(groupbox_sz, small_deployable_tab))) {

            calliope::menu.components.colorpicker(XS("Stash Color"), ColorSettings::Stash_Color, true);
            calliope::menu.components.checkbox(XS("Stash"), m_settings::Stash);

            calliope::menu.components.colorpicker(XS("Recycler Color"), ColorSettings::Recycler_Color, true);
            calliope::menu.components.checkbox(XS("Recycler"), m_settings::Recycler);

            calliope::menu.components.colorpicker(XS("Workbench1 Color"), ColorSettings::Workbench1_Color, true);
            calliope::menu.components.checkbox(XS("T1-Workbench"), m_settings::T1Workbench);

            calliope::menu.components.colorpicker(XS("Workbench2 Color"), ColorSettings::Workbench2_Color, true);
            calliope::menu.components.checkbox(XS("T2-Workbench"), m_settings::T2Workbench);

            calliope::menu.components.colorpicker(XS("Workbench3 Color"), ColorSettings::Workbench3_Color, true);
            calliope::menu.components.checkbox(XS("T3-Workbench"), m_settings::T3Workbench);

            calliope::menu.components.slider<float>(XS("Deployable Distance"), XS(""), m_settings::MaxDeployableDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_ctx_2 = calliope::menu.components.groupbox(XS("ToolCupboard"), calliope::vec2_t(50, WorldStartSize + 10 + small_deployable_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_deployable_tab - 25 - WorldStartSize))) {

            calliope::menu.components.colorpicker(XS("Cupboard Color"), ColorSettings::Cupboard_Color, true);
            calliope::menu.components.checkbox(XS("Cupboard"), m_settings::cupboard);

            calliope::menu.components.colorpicker(XS("CAuthedPlayers Color"), ColorSettings::CAuthedPlayers_Color, true);
            calliope::menu.components.checkbox(XS("Authed-Players"), m_settings::AuthorizedPlayers);

            calliope::menu.components.colorpicker(XS("CUpkeep Color"), ColorSettings::CUpKeep_Color, true);
            calliope::menu.components.checkbox(XS("Upkeep"), m_settings::TC_Upkeep);

            calliope::menu.components.checkbox(XS("TC-Health"), m_settings::TC_Health);

            calliope::menu.components.slider<float>(XS("Authed Distance"), XS(""), m_settings::AuthorizedPlayersDistance, 0, 500);
            calliope::menu.components.slider<float>(XS("TC Distance"), XS(""), m_settings::MaxTCDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_two = calliope::menu.components.groupbox(XS("Crates"), calliope::vec2_t(60 + groupbox_sz, WorldStartSize), calliope::vec2_t(groupbox_sz, groupbox_sz_y - 15 - WorldStartSize))) {

            calliope::menu.components.colorpicker(XS("Airdrop Color"), ColorSettings::Airdrop_Color, true);
            calliope::menu.components.checkbox(XS("Airdrop"), m_settings::SupplyDrop);

            calliope::menu.components.colorpicker(XS("BradleyCrate Color"), ColorSettings::BradleyCrate_Color, true);
            calliope::menu.components.checkbox(XS("Bradley-Crate"), m_settings::BradleyCrate);

            calliope::menu.components.colorpicker(XS("HeliCrate Color"), ColorSettings::HeliCrate_Color, true);
            calliope::menu.components.checkbox(XS("Heli-Crate"), m_settings::HeliCrate);

            calliope::menu.components.colorpicker(XS("HackableCrate Color"), ColorSettings::HackableCrate_Color, true);
            calliope::menu.components.checkbox(XS("Hackable-Crate"), m_settings::HackableCrate);

            calliope::menu.components.colorpicker(XS("BasicCrate Color"), ColorSettings::BasicCrate_Color, true);
            calliope::menu.components.checkbox(XS("Basic-Crate"), m_settings::BasicCrate);

            calliope::menu.components.colorpicker(XS("NormalCrate Color"), ColorSettings::NormalCrate_Color, true);
            calliope::menu.components.checkbox(XS("Normal-Crate"), m_settings::NormalCrate);

            calliope::menu.components.colorpicker(XS("MilitaryCrate Color"), ColorSettings::MilitaryCrate_Color, true);
            calliope::menu.components.checkbox(XS("Military-Crate"), m_settings::MilitaryCrate);

            calliope::menu.components.colorpicker(XS("EliteCrate Color"), ColorSettings::EliteCrate_Color, true);
            calliope::menu.components.checkbox(XS("Elite-Crate"), m_settings::EliteCrate);

            calliope::menu.components.colorpicker(XS("LootBarrel Color"), ColorSettings::LootBarrel_Color, true);
            calliope::menu.components.checkbox(XS("Loot-Barrel"), m_settings::LootBarrel);

            calliope::menu.components.slider<float>(XS("Airdrop Distance"), XS(""), m_settings::MaxSupplyDropDistance, 0, 500);
            calliope::menu.components.slider<float>(XS("Crate Distance"), XS(""), m_settings::MaxCrateDistance, 0, 500);

            if (m_settings::HackableCrate)
            {
                m_settings::HackableCrateFlags = true;
                m_settings::HackableCrateTimer = true;
            }

            calliope::menu.components.end_groupbox();
        }
    }
    else if (WorldPage == 2)
    {
        if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Traps"), calliope::vec2_t(50, WorldStartSize), calliope::vec2_t(groupbox_sz, small_traps_tab))) {

            calliope::menu.components.colorpicker(XS("ShotgunTrap Color"), ColorSettings::ShotgunTrap_Color, true);
            calliope::menu.components.checkbox(XS("Shotgun-Trap"), m_settings::ShotgunTrap);

            calliope::menu.components.colorpicker(XS("FlameTurret Color"), ColorSettings::FlameTurret_Color, true);
            calliope::menu.components.checkbox(XS("Flame-Turret"), m_settings::FlameTurret);

            calliope::menu.components.colorpicker(XS("BearTrap Color"), ColorSettings::BearTrap_Color, true);
            calliope::menu.components.checkbox(XS("Bear-Trap"), m_settings::BearTrap);

            calliope::menu.components.colorpicker(XS("SpikesTrap Color"), ColorSettings::SpikesTrap_Color, true);
            calliope::menu.components.checkbox(XS("Spikes-Trap"), m_settings::SpikesTrap);

            calliope::menu.components.colorpicker(XS("LandMine Color"), ColorSettings::LandMine_Color, true);
            calliope::menu.components.checkbox(XS("Land-Mine"), m_settings::LandMine);

            calliope::menu.components.slider<float>(XS("Traps Distance"), XS(""), m_settings::MaxTrapsDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_ctx_2 = calliope::menu.components.groupbox(XS("Dropped Items"), calliope::vec2_t(50, WorldStartSize + 10 + small_traps_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_traps_tab - 25 - WorldStartSize))) {

            calliope::menu.components.colorpicker(XS("DroppedItems Color"), ColorSettings::DroppedItems_Color, true);
            calliope::menu.components.checkbox(XS("Dropped-Items"), m_settings::DroppedItems);

            calliope::menu.components.colorpicker(XS("DroppedChams Color"), ColorSettings::DroppedChams_Color, true);
            calliope::menu.components.checkbox(XS("Dropped-Chams"), m_settings::DroppedItemsChams);

            calliope::menu.components.multi_dropdown(XS("Hide-Selected-Items"), { ("Weapon-Mods"), ("Melee-Items"), ("Tier1-Weapons"), ("Tier2-Weapons"), ("Tier3-Weapons"), ("Workbenches"), ("Resources"), ("Armor"), ("Tools"), ("Explosives"), ("Medical"), ("Ammo"), ("Components") }, m_settings::DroppedOptions);

            calliope::menu.components.slider<float>(XS("Dropped Distance"), XS(""), m_settings::MaxDroppedDistance, 0, 500);

            {
                if (m_settings::DroppedOptions[0])
                    m_settings::HideWeaponMods = true;
                else
                    m_settings::HideWeaponMods = false;

                if (m_settings::DroppedOptions[1])
                    m_settings::HideMeleeItems = true;
                else
                    m_settings::HideMeleeItems = false;

                if (m_settings::DroppedOptions[2])
                    m_settings::HideTier1Weapons = true;
                else
                    m_settings::HideTier1Weapons = false;

                if (m_settings::DroppedOptions[3])
                    m_settings::HideTier2Weapons = true;
                else
                    m_settings::HideTier2Weapons = false;

                if (m_settings::DroppedOptions[4])
                    m_settings::HideTier3Weapons = true;
                else
                    m_settings::HideTier3Weapons = false;

                if (m_settings::DroppedOptions[5])
                    m_settings::HideWorkbenches = true;
                else
                    m_settings::HideWorkbenches = false;

                if (m_settings::DroppedOptions[6])
                    m_settings::HideResources = true;
                else
                    m_settings::HideResources = false;

                if (m_settings::DroppedOptions[7])
                    m_settings::HideArmor = true;
                else
                    m_settings::HideArmor = false;

                if (m_settings::DroppedOptions[8])
                    m_settings::HideTools = true;
                else
                    m_settings::HideTools = false;

                if (m_settings::DroppedOptions[9])
                    m_settings::HideExplosive = true;
                else
                    m_settings::HideExplosive = false;

                if (m_settings::DroppedOptions[10])
                    m_settings::HideMedical = true;
                else
                    m_settings::HideMedical = false;

                if (m_settings::DroppedOptions[11])
                    m_settings::HideAmmo = true;
                else
                    m_settings::HideAmmo = false;

                if (m_settings::DroppedOptions[12])
                    m_settings::HideComponents = true;
                else
                    m_settings::HideComponents = false;
            }

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_ctx_2 = calliope::menu.components.groupbox(XS("Turret"), calliope::vec2_t(60 + groupbox_sz, WorldStartSize), calliope::vec2_t(groupbox_sz, groupbox_sz_y - 15 - WorldStartSize))) {

            calliope::menu.components.colorpicker(XS("Turret Color"), ColorSettings::Turret_Color, true);
            calliope::menu.components.checkbox(XS("Turret"), m_settings::AutoTurret);

            calliope::menu.components.colorpicker(XS("TAuthedPlayers Color"), ColorSettings::TAuthedPlayers_Color, true);
            calliope::menu.components.checkbox(XS("TAuthed-Players"), m_settings::TurretAuthorizedPlayers);

            calliope::menu.components.colorpicker(XS("EquippedFlag Color"), ColorSettings::TEquipedFlag_Color, true);
            calliope::menu.components.checkbox(XS("Equipped-Flag"), m_settings::TurretEquippedFlags);

            calliope::menu.components.colorpicker(XS("TShowOnline Color"), ColorSettings::ShowOnline_Color, true);
            calliope::menu.components.checkbox(XS("Show-Online"), m_settings::TurretOnFlags);

            calliope::menu.components.colorpicker(XS("TTurning Color"), ColorSettings::TurningFlags_Color, true);
            calliope::menu.components.checkbox(XS("Turning-Flags"), m_settings::TurretTurningFlag);

            calliope::menu.components.colorpicker(XS("TRange Color"), ColorSettings::Range_Color, true);
            calliope::menu.components.checkbox(XS("Range"), m_settings::TurretRange);

            calliope::menu.components.checkbox(XS("Turret-Health"), m_settings::TurretHealth);
            calliope::menu.components.slider<float>(XS("Turret Distance"), XS(""), m_settings::MaxTurretDistance, 0, 500);

            calliope::menu.components.end_groupbox();
        }
    }
    else if (WorldPage == 3)
    {
        if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Animals"), calliope::vec2_t(50, WorldStartSize), calliope::vec2_t(groupbox_sz, groupbox_sz_y - WorldStartSize - 15))) {
    
            calliope::menu.components.colorpicker(XS("Horse Color"), ColorSettings::Horse, true);
            calliope::menu.components.checkbox(XS("Horse"), m_settings::horseEsp);
    
            calliope::menu.components.colorpicker(XS("Bear Color"), ColorSettings::Bear, true);
            calliope::menu.components.checkbox(XS("Bear"), m_settings::Bear);
    
            calliope::menu.components.colorpicker(XS("Boar Color"), ColorSettings::Boar, true);
            calliope::menu.components.checkbox(XS("Boar"), m_settings::Boar);
    
            calliope::menu.components.colorpicker(XS("Stag Color"), ColorSettings::Stag, true);
            calliope::menu.components.checkbox(XS("Stag"), m_settings::Stag);
    
            calliope::menu.components.colorpicker(XS("Wolf Color"), ColorSettings::Wolf, true);
            calliope::menu.components.checkbox(XS("Wolf"), m_settings::Wolf);
    
            calliope::menu.components.slider<float>(XS("Animal Distance"), XS(""), m_settings::MaxAnimalDistance, 0, 500);
    
            calliope::menu.components.end_groupbox();
        }
    
        if (auto groupbox_ctx_2 = calliope::menu.components.groupbox(XS("Vehicles"), calliope::vec2_t(60 + groupbox_sz, WorldStartSize), calliope::vec2_t(groupbox_sz, groupbox_sz_y - 15 - WorldStartSize))) {
    
            calliope::menu.components.colorpicker(XS("PatrolHeli Color"), ColorSettings::PatrolHeli_Color, true);
            calliope::menu.components.checkbox(XS("Patrol-Heli"), m_settings::PatrolHelicopter);
    
            calliope::menu.components.colorpicker(XS("Bradley Color"), ColorSettings::Bradley_Color, true);
            calliope::menu.components.checkbox(XS("Bradley"), m_settings::BradleyAPC);
    
            calliope::menu.components.colorpicker(XS("MiniCopter Color"), ColorSettings::Minicopter_Color, true);
            calliope::menu.components.checkbox(XS("MiniCopter"), m_settings::Minicopter);
    
            calliope::menu.components.colorpicker(XS("ScrapHeli Color"), ColorSettings::ScrapHeli_Color, true);
            calliope::menu.components.checkbox(XS("ScrapHeli"), m_settings::ScrapHeli);
    
            calliope::menu.components.colorpicker(XS("TugBoat Color"), ColorSettings::TugBoat_Color, true);
            calliope::menu.components.checkbox(XS("TugBoat"), m_settings::TugBoat);
    
            calliope::menu.components.colorpicker(XS("RHIB Color"), ColorSettings::RHIB_Color, true);
            calliope::menu.components.checkbox(XS("RHIB"), m_settings::Rhib);
    
            calliope::menu.components.colorpicker(XS("RowBoat Color"), ColorSettings::RowBoat_Color, true);
            calliope::menu.components.checkbox(XS("RowBoat"), m_settings::Rowboat);
    
            calliope::menu.components.slider<float>(XS("Vehicle Distance"), XS(""), m_settings::MaxVehicleDistance, 0, 500);
            calliope::menu.components.slider<float>(XS("APC Distance"), XS(""), m_settings::MaxAPCDistance, 0, 5000);
    
    
            calliope::menu.components.end_groupbox();
        }
    }
}

int LocalPage = 0;
int LocalStartSize = 30;
void LocalTab()
{
    calliope::menu.components.sidecombo(XS("Page"), { "Page 1", "Page 2" }, LocalPage, calliope::vec2_t(50, 0), calliope::vec2_t(full_groupbox_sz, 20));

    if (LocalPage == 0) {
        if (auto groupbox_ctx2 = calliope::menu.components.groupbox(XS("Movement"), calliope::vec2_t(50, LocalStartSize), calliope::vec2_t(groupbox_sz, groupbox_sz_y - LocalStartSize - 15))) {

            calliope::menu.components.checkbox(XS("SpiderMan"), m_settings::SpiderMan);
            calliope::menu.components.checkbox(XS("Smaller-Local-Radius"), m_settings::SmallerLocalRadius);
            calliope::menu.components.checkbox(XS("Admin-Flags"), m_settings::AdminFlags);
            calliope::menu.components.checkbox(XS("Infinite-Jump"), m_settings::InfiniteJump);
            calliope::menu.components.checkbox(XS("Omni-Sprint"), m_settings::OmniSprint);
            calliope::menu.components.checkbox(XS("Always-Sprint"), m_settings::AlwaysSprint);
            calliope::menu.components.checkbox(XS("No-Movement-Restrictions"), m_settings::NoMovementRestrictions);
            calliope::menu.components.checkbox(XS("BlockServerCommands"), m_settings::BlockServerCommands);
            calliope::menu.components.checkbox(XS("Adjust-NoClip-Speed"), m_settings::AdjustNoClipSpeed);
            calliope::menu.components.checkbox(XS("No-Clip"), m_settings::AdminCheat);
            calliope::menu.components.keybind(XS("NoClip Bind"), (int&)m_settings::AdminCheatKey, true);
            calliope::menu.components.checkbox(XS("Debug-Camera"), m_settings::DebugCamera);
            calliope::menu.components.keybind(XS("DebugCamera Key"), (int&)m_settings::DebugCameraKey, true);
            calliope::menu.components.checkbox(XS("Silent-Walk"), m_settings::SilentWalk);
            calliope::menu.components.keybind(XS("SilentWalk Bind"), (int&)m_settings::SilentWalkKey, true);
            calliope::menu.components.checkbox(XS("Interactive-Debug"), m_settings::InteractiveDebug);
            calliope::menu.components.keybind(XS("Interactive Bind"), (int&)m_settings::InteractiveKey, true);
            // calliope::menu.components.checkbox(XS("Teleport-Max-Height"), m_settings::TeleportMax);
            // calliope::menu.components.keybind(XS("TeleportMax Bind"), (int&)m_settings::TeleportMaxKey, true);


            calliope::menu.components.end_groupbox();
        }


        if (auto groupbox_two = calliope::menu.components.groupbox(XS("Flyhack"), calliope::vec2_t(60 + groupbox_sz, LocalStartSize), calliope::vec2_t(groupbox_sz, small_flyhack_tab))) {

            calliope::menu.components.checkbox(XS("Flyhack-Indicator"), m_settings::Flyhack_Indicator);
            calliope::menu.components.checkbox(XS("Anti-FlyhackKick"), m_settings::AntiFlyKick);
            calliope::menu.components.checkbox(XS("Anti-DeathBarrier"), m_settings::AntiDeathBarrier);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_two2 = calliope::menu.components.groupbox(XS("Misc"), calliope::vec2_t(60 + groupbox_sz, LocalStartSize + 10 + small_flyhack_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_flyhack_tab - LocalStartSize - 25))) {

            calliope::menu.components.checkbox(XS("Name-Spoofer"), m_settings::NameSpoofer);
            calliope::menu.components.checkbox(XS("Spin-bot"), m_settings::Spinbot);
            calliope::menu.components.checkbox(XS("Anti-DebugCamera"), m_settings::FixDebugCamera);

            calliope::menu.components.checkbox(XS("Instant-Revive"), m_settings::InstantRevive);
            calliope::menu.components.keybind(XS("InstantRevive Bind"), (int&)m_settings::InstantReviveKey, true);

            calliope::menu.components.checkbox(XS("Keep-Target-Alive"), m_settings::KeepTargetAlive);
            calliope::menu.components.keybind(XS("KeepAlive Bind"), (int&)m_settings::KeepAliveKey, true);

            calliope::menu.components.checkbox(XS("Suicide"), m_settings::Suicide);
            calliope::menu.components.keybind(XS("Suicide Bind"), (int&)m_settings::SuicideKey, true);


            calliope::menu.components.end_groupbox();
        }
    }
    else if (LocalPage == 1)
    {
        if (auto groupbox_two = calliope::menu.components.groupbox(XS("Instant"), calliope::vec2_t(50, LocalStartSize), calliope::vec2_t(groupbox_sz, small_instant_tab))) {

            calliope::menu.components.checkbox(XS("Instant-Loot"), m_settings::InstantLoot);
            calliope::menu.components.checkbox(XS("Instant-Heal"), m_settings::InstantHeal);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_two2 = calliope::menu.components.groupbox(XS("Collision"), calliope::vec2_t(50, LocalStartSize + 10 + small_instant_tab), calliope::vec2_t(groupbox_sz, small_collision_tab))) {

            calliope::menu.components.checkbox(XS("Trees"), m_settings::IgnoreTrees);
            calliope::menu.components.checkbox(XS("Players"), m_settings::IgnorePlayers);

            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_two2 = calliope::menu.components.groupbox(XS("Player Reporter"), calliope::vec2_t(50, LocalStartSize + 10 + small_instant_tab + 10 + small_collision_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_instant_tab  - small_collision_tab - LocalStartSize - 35))) {

            calliope::menu.components.checkbox(XS("Report AimTarget"), m_settings::report_player);
            calliope::menu.components.keybind(XS("Report Bind"), (int&)m_settings::report_key, true);

            calliope::menu.components.end_groupbox();
        }
        
        if (auto groupbox_two2 = calliope::menu.components.groupbox(XS("Camera"), calliope::vec2_t(60 + groupbox_sz, LocalStartSize), calliope::vec2_t(groupbox_sz, small_misc_tab))) {

            calliope::menu.components.checkbox(XS("ChangeCameraMode"), m_settings::ChangeCameraMode);

            calliope::menu.components.dropdown(XS("Camera-Mode"), { ("1st Person"), ("3rd Person"), ("Eyes"), ("2nd Person?"), ("Bottom Camera") }, (int&)m_settings::CameraMode);
            //calliope::menu.components.slider<int>(XS("Camera-Mode"), XS(""), (int&)m_settings::CameraMode, 0, 4);
            calliope::menu.components.slider<float>(XS("Camera-Distance"), XS(""), m_settings::CameraDistance, 0, 10);


            calliope::menu.components.end_groupbox();
        }

        if (auto groupbox_two2 = calliope::menu.components.groupbox(XS("Save Position"), calliope::vec2_t(60 + groupbox_sz, LocalStartSize + 10 + small_misc_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_misc_tab - LocalStartSize - 25))) {

            calliope::menu.components.checkbox(XS("Save-Position"), m_settings::SavePos);
            calliope::menu.components.keybind(XS("SavePosition Bind"), (int&)m_settings::SavePosKey, true);

            calliope::menu.components.checkbox(XS("Save-House"), m_settings::SaveHouse);
            calliope::menu.components.keybind(XS("SaveHouse Bind"), (int&)m_settings::SaveHouseKey, true);


            calliope::menu.components.end_groupbox();
        }
    }
}

void MiscTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Automatic"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_auto_tab))) {

        calliope::menu.components.checkbox(XS("Auto-Farm-Tree"), m_settings::AutoFarmTree);
        calliope::menu.components.checkbox(XS("Auto-Farm-Ore"), m_settings::AutoFarmOre);
        calliope::menu.components.checkbox(XS("Always-Hotspot"), m_settings::AlwaysHotspot);
        calliope::menu.components.checkbox(XS("Auto-Upgrade"), m_settings::AutoUpgrade);
        calliope::menu.components.dropdown(XS("BuildingGrade"), { ("Wood"), ("Stone"), ("Metal"), ("HQM") }, m_settings::BuildingGrade);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx2 = calliope::menu.components.groupbox(XS("Prefab Spawner"), calliope::vec2_t(50, 10 + small_auto_tab), calliope::vec2_t(groupbox_sz, small_prefab_tab))) {

        calliope::menu.components.checkbox(XS("Spawn-Amongus"), m_settings::AmongusPrefabSpawn);
        calliope::menu.components.keybind(XS("Amongus Bind"), (int&)m_settings::AmongusKey, true);

        calliope::menu.components.checkbox(XS("Spawn-Herbert"), m_settings::HerbertPrefabSpawn);
        calliope::menu.components.keybind(XS("Herbert Bind"), (int&)m_settings::HerbertKey, true);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx2 = calliope::menu.components.groupbox(XS("Speedhack"), calliope::vec2_t(50, 10 + small_auto_tab + 10 + small_prefab_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_auto_tab - small_prefab_tab - 35))) {

        calliope::menu.components.checkbox(XS("Speedhack"), m_settings::Speedhack);
        calliope::menu.components.keybind(XS("Speedhack Bind"), (int&)m_settings::SpeedhackKey, true);

        calliope::menu.components.slider<float>(XS("Speedhack Amount"), XS(""), m_settings::SpeedhackSpeed, 0, 10);

        calliope::menu.components.end_groupbox();
    }



    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Spam"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, small_spam_tab))) {

        calliope::menu.components.checkbox(XS("Door-Spammer"), m_settings::DoorSpammer);

        calliope::menu.components.checkbox(XS("Gesture-Spam"), m_settings::GestureSpam);
        calliope::menu.components.dropdown(XS("Gesture"), { ("None"), ("Clap"), ("Friendly"), ("ThumbsDown"), ("ThumbsUp"), ("Ok"), ("Point"), ("Shrug"), ("Victory"), ("Wave") }, m_settings::gesture);

        calliope::menu.components.checkbox(XS("Hammer-Spam"), m_settings::HammerSpam);
        calliope::menu.components.keybind(XS("HammerSpam Bind"), (int&)m_settings::HammerSpamKey, true);
        calliope::menu.components.dropdown(XS("Material"), { ("Glass"), ("Water") }, m_settings::HammerMaterialType);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two2 = calliope::menu.components.groupbox(XS("FOV"), calliope::vec2_t(60 + groupbox_sz, 10 + small_spam_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_spam_tab - 25))) {

        calliope::menu.components.checkbox(XS("Player-Fov"), m_settings::PlayerFov);
        calliope::menu.components.checkbox(XS("Zoom"), m_settings::Zoom);
        calliope::menu.components.keybind(XS("Zoom Bind"), (int&)m_settings::ZoomKey, true);

        calliope::menu.components.slider<float>(XS("Player-Fov Amount"), XS(""), m_settings::PlayerFovAmount, 0, 140);
        calliope::menu.components.slider<float>(XS("Zoom Amount"), XS(""), m_settings::ZoomAmount, 0, 50);


        calliope::menu.components.end_groupbox();
    }


}

void WeatherTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Skydome"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_bright_tab))) {

        calliope::menu.components.checkbox(XS("Bright-Night"), m_settings::Brightnight);

        calliope::menu.components.colorpicker(XS("Ambient Color"), ColorSettings::Ambient_Color, true);
        calliope::menu.components.checkbox(XS("Bright-Ambient"), m_settings::BrightAmbient);

        calliope::menu.components.checkbox(XS("Bright-Cave"), m_settings::BrightCave);


        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx2 = calliope::menu.components.groupbox(XS("Sky Adjustments"), calliope::vec2_t(50, 10 + small_bright_tab), calliope::vec2_t(groupbox_sz, small_sky_tab))) {

        calliope::menu.components.checkbox(XS("Stars"), m_settings::Stars);

        calliope::menu.components.colorpicker(XS("Skybox Color"), ColorSettings::SkyBox_Color, true);
        calliope::menu.components.checkbox(XS("Sky-Color"), m_settings::SkyColorNight);

        calliope::menu.components.checkbox(XS("Sharp-Clouds"), m_settings::SharpClouds);


        if (m_settings::SkyColorNight) {
            m_settings::AtmosphereContrast = false;
            m_settings::SkyColorDay = true;
        }
        else
            m_settings::SkyColorDay = false;

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx2 = calliope::menu.components.groupbox(XS("Time"), calliope::vec2_t(50, 10 + small_bright_tab + 10 + small_sky_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_bright_tab - small_sky_tab - 35))) {

        calliope::menu.components.checkbox(XS("Time-Changer"), m_settings::TimeChanger);
        calliope::menu.components.slider<float>(XS("Game-Time"), XS(""), m_settings::GameTime, 0, 24);


        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Weather"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, small_weather_tab))) {
        // calliope::menu.components.checkbox(XS("Enable-Weather"), m_settings::Weather);
        calliope::menu.components.checkbox(XS("Atmosphere"), m_settings::AtmosphereContrast);
        calliope::menu.components.checkbox(XS("Rainbows"), m_settings::Rainbows);

        if (m_settings::AtmosphereContrast)
        {
            m_settings::SkyColorDay = false;
            m_settings::SkyColorNight = false;
        }

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two2 = calliope::menu.components.groupbox(XS("Remove Weather"), calliope::vec2_t(60 + groupbox_sz, 10 + small_weather_tab), calliope::vec2_t(groupbox_sz, small_nosky_tab))) {
        calliope::menu.components.checkbox(XS("No-Clouds"), m_settings::NoClouds);
        calliope::menu.components.checkbox(XS("No-Sun"), m_settings::NoSun);
        calliope::menu.components.checkbox(XS("No-Fog"), m_settings::NoFog);
        calliope::menu.components.checkbox(XS("No-Rain"), m_settings::NoRain);
        calliope::menu.components.checkbox(XS("No-Thunder"), m_settings::NoThunder);
        calliope::menu.components.checkbox(XS("No-Wind"), m_settings::NoWind);


        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two3 = calliope::menu.components.groupbox(XS("Rainbow-Sky"), calliope::vec2_t(60 + groupbox_sz, 10 + small_weather_tab + 10 + small_nosky_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_weather_tab - small_nosky_tab - 35))) {

        calliope::menu.components.checkbox(XS("Rainbow-Sky"), m_settings::RainbowSky);
        calliope::menu.components.slider<float>(XS("SkyValue"), XS(""), m_settings::RainbowAmount, 0, 100);


        calliope::menu.components.end_groupbox();
    }

}

void WeaponsTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Weapon"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_weapons_tab))) {

        calliope::menu.components.checkbox(XS("No-Attack-Restrictions"), m_settings::NoAttackRestrictions);
        calliope::menu.components.checkbox(XS("Recoil-Modifier"), m_settings::ChangeRecoil);
        calliope::menu.components.checkbox(XS("Thick-Bullet"), m_settings::NormalThickBullet);
        calliope::menu.components.checkbox(XS("Fast-Bullet"), m_settings::NormalFastBullet);
        calliope::menu.components.checkbox(XS("Force-Automatic"), m_settings::ForceAutomatic);
        calliope::menu.components.checkbox(XS("No-Sway"), m_settings::NoSway);
        calliope::menu.components.checkbox(XS("Instant-Eoka"), m_settings::InstantEoka);
        calliope::menu.components.checkbox(XS("No-Weapon-Bob"), m_settings::NoWeaponBob);
        calliope::menu.components.checkbox(XS("No-Animations"), m_settings::RemoveAttackAnimations);
        calliope::menu.components.checkbox(XS("Long-Melee"), m_settings::LongMelee);

        if (m_settings::ChangeRecoil)
            calliope::menu.components.slider<float>(XS("Recoil"), XS(""), m_settings::recoilPercent, 0, 100);
        if (m_settings::NormalThickBullet)
            calliope::menu.components.slider<float>(XS("Thickness"), XS(""), m_settings::NormalThickBulletThickness, 0, 1.44);

        if (m_settings::RotationAimbot)
            calliope::menu.components.slider<float>(XS("Spread-Amount"), XS(""), m_settings::SilentSpread, 0, 100);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("HitSounds"), calliope::vec2_t(50, 10 + small_weapons_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_weapons_tab - 25))) {

        calliope::menu.components.checkbox(XS("Disable-HitSounds"), m_settings::DisableHitSounds);
        calliope::menu.components.checkbox(XS("Custom-HitSounds"), m_settings::CustomHitSounds);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Misc"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, small_weapon_tab2))) {

        calliope::menu.components.checkbox(XS("Weapon-Spammer"), m_settings::WeaponSpammer);
        calliope::menu.components.keybind(XS("WeaponSpammer Bind"), (int&)m_settings::WeaponSpamKey, true);

        calliope::menu.components.slider<float>(XS("Weapon-Spammer-Delay"), XS(""), m_settings::WeaponSpamDelay, 0, 20);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Load Effects"), calliope::vec2_t(60 + groupbox_sz, 10 + small_weapon_tab2), calliope::vec2_t(groupbox_sz, small_loadeffects_tab))) {

        calliope::menu.components.checkbox(XS("Load-Explosion"), m_settings::LoadExplosionEffect);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Kill Effects"), calliope::vec2_t(60 + groupbox_sz, 10 + small_weapon_tab2 + 10 + small_loadeffects_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_loadeffects_tab - small_weapon_tab2 - 35))) {

        calliope::menu.components.checkbox(XS("Explosion-Effect"), m_settings::ExplosionEffect);
        if (m_settings::ExplosionEffect)
        {
            m_settings::GhostEffect = false;
            m_settings::SelectedKillEffect = 0;
        }
        calliope::menu.components.checkbox(XS("Ghost-Effect"), m_settings::GhostEffect);
        if (m_settings::GhostEffect)
        {
            m_settings::ExplosionEffect = false;
            m_settings::SelectedKillEffect = 1;
        }

        if (m_settings::ExplosionEffect || m_settings::GhostEffect)
            m_settings::KillEffects = true;
        else
            m_settings::KillEffects = false;

        calliope::menu.components.end_groupbox();
    }

}
void ColorsTab()
{
    if (auto groupbox_ctx = calliope::menu.components.groupbox(XS("Text Settings"), calliope::vec2_t(50, 0), calliope::vec2_t(groupbox_sz, small_text_tab))) {

        calliope::menu.components.checkbox(XS("Font-Changer"), m_settings::FontChanger);
        calliope::menu.components.checkbox(XS("Player-Outlined-Text"), m_settings::OutlinedText);
        if (m_settings::OutlinedText)
            m_settings::ShadedText = false;
        calliope::menu.components.checkbox(XS("Player-Shadowed-Text"), m_settings::ShadedText);
        if (m_settings::ShadedText)
            m_settings::OutlinedText = false;
        calliope::menu.components.checkbox(XS("World-Outlined-Text"), m_settings::WorldOutlinedText);
        if (m_settings::WorldOutlinedText)
            m_settings::WorldShadedText = false;
        calliope::menu.components.checkbox(XS("World-Shaded-Text"), m_settings::WorldShadedText);
        if (m_settings::WorldShadedText)
            m_settings::WorldOutlinedText = false;

        calliope::menu.components.slider<float>(XS("Player-Font-Size"), XS(""), m_settings::ESPFontsize, 0, 15);
        calliope::menu.components.slider<float>(XS("World-Font-Size"), XS(""), m_settings::WorldFontSize, 0, 15);

        calliope::menu.components.dropdown(XS("Font"), { ("Default"), ("Pixel"), ("Verdana"), ("Division") }, m_settings::fonttype);


        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_ctx2 = calliope::menu.components.groupbox(XS("Menu Colors"), calliope::vec2_t(50, 10 + small_text_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_text_tab - 25))) {

        calliope::menu.components.colorpicker(XS("Menu Color"), calliope::globals::menu_accent, false);
        calliope::menu.components.end_groupbox();
    }


    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Settings"), calliope::vec2_t(60 + groupbox_sz, 0), calliope::vec2_t(groupbox_sz, small_config_tab))) {

        calliope::menu.components.dropdown(XS("Config"), { ("Legit"), ("Rage"), ("Config1"), ("Config2"), ("Config3") }, m_settings::SelectedConfig);
        calliope::menu.components.button(XS("Save-Config"), Configs::SaveConfig);
        calliope::menu.components.button(XS("Load-Config"), Configs::LoadConfig);

        calliope::menu.components.end_groupbox();
    }

    if (auto groupbox_two = calliope::menu.components.groupbox(XS("Resets"), calliope::vec2_t(60 + groupbox_sz, 10 + small_config_tab), calliope::vec2_t(groupbox_sz, groupbox_sz_y - small_config_tab - 25))) {

        calliope::menu.components.button(XS("Reset-PlayerModels"), reset_player_model);
        calliope::menu.components.button(XS("Reset-LOS Points"), Buttons::ClearLOSPoints);
        calliope::menu.components.button(XS("Clear-RaidCache"), Buttons::ClearRaidCache);

        calliope::menu.components.end_groupbox();
    }

}
void GUI::DrawMenu()
{
    if (calliope::menu.components.window(XS("Serotonin"), calliope::vec2_t(250, 250), calliope::vec2_t(600, 400), calliope::menu_t::window_flags_none)) {
        switch (auto selected_tab = calliope::menu.components.tabs({ XS("Aimbot"), XS("Rage"), XS("Visuals"), XS("Chams"), XS("World"), XS("Player"), XS("Misc"), XS("Weather"), XS("Weapon"), XS("Settings") })) {
        case 0: {
            AimbotTab();
            break;
        }
        case 1: {
            RageTab();
            break;
        }
        case 2: {
            PlayersVisuals();
            break;
        }
        case 3: {
            ChamsTab();
            break;
        }
        case 4: {
            WorldTab();
            break;
        }
        case 5: {
            LocalTab();
            break;
        }
        case 6: {
            MiscTab();
            break;
        }
        case 7: {
            WeatherTab();
            break;
        }
        case 8: {
            WeaponsTab();
            break;
        }
        case 9: {
            ColorsTab();
            break;
        }
        }
        calliope::menu.components.end_window();
    }
}
