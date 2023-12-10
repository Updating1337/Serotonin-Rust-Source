#include "../../calliope.hpp"

// @note : clowie - ahh these r always a doozy.

// pasta from stackoverflow 
inline calliope::color_t hex_to_rgb(std::string hex) {
    calliope::color_t out;

    auto SplitWithCharacters = [](const std::string& str, int splitLength) -> std::vector<std::string> {
        int NumSubstrings = str.length() / splitLength;
        std::vector<std::string> ret;

        for (int i = 0; i < NumSubstrings; i++) {
            ret.push_back(str.substr(i * splitLength, splitLength));
        }

        // If there are leftover characters, create a shorter item at the end.
        if (str.length() % splitLength != 0) {
            ret.push_back(str.substr(splitLength * NumSubstrings));
        }

        return ret;
        };

    if (hex.at(0) == '#') {
        hex.erase(0, 1);
    }
    else {
        return out;
    }

    std::vector<std::string> colori = SplitWithCharacters(hex, 2);

    out = calliope::color_t(stoi_c(colori[0], nullptr, 16),
        stoi_c(colori[1], nullptr, 16),
        stoi_c(colori[2], nullptr, 16),
        stoi_c(colori[3], nullptr, 16)
    );

    return out;
}

void calliope::menu_t::components_t::colorpicker(const char* title, color_t& color, bool inlined) {
    const static color_t hue_colors[7] = {
        color_t(255, 0, 0, 255),
        color_t(255, 255, 0, 255),
        color_t(0, 255, 0, 255),
        color_t(0, 255, 255, 255),
        color_t(0, 0, 255, 255),
        color_t(255, 0, 255, 255),
        color_t(255, 0, 0, 255)
    };

    const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;

    if (!menu.m_current_groupbox)
        return;

    auto color_preview_position = menu.m_current_groupbox->cursor_position + vec2_t(menu.m_current_groupbox->size.x - 45, 0);
    auto color_preview_size = vec2_t(20, 10);

    const bool preview_hovered = menu.mouse_in_rect(color_preview_position, color_preview_position + color_preview_size);

    auto color_picker_position = color_preview_position + color_preview_size;
    auto color_picker_size = vec2_t(180, 175);

    const bool picker_window_hovered = menu.mouse_in_rect(color_picker_position, color_picker_position + color_picker_size);

    const bool in_use = menu.window_ctx.m_active_hash == util::hash(title);
    const bool alt_in_use = menu.window_ctx.m_active_hash == util::hash(title) + 2;

    auto alt_window_size = vec2_t(85, 60);
    const bool alt_window_hovered = menu.mouse_in_rect(color_picker_position, color_picker_position + alt_window_size);

    if (alt_in_use && !alt_window_hovered && (menu.mouse_active && !menu.old_mouse_active)) {
        menu.window_ctx.m_active_hash = 0;
    }

    if (in_use && !picker_window_hovered && (menu.mouse_active && !menu.old_mouse_active)) {
        menu.window_ctx.m_active_hash = 0;
    }

    if (preview_hovered && (menu.mouse_active && !menu.old_mouse_active) && was_empty_last_hash) {
        menu.window_ctx.m_active_hash = util::hash(title);
    }
    if (preview_hovered && (util::is_key_pressed(RustStructs::Mouse1)) && was_empty_last_hash) {
        menu.window_ctx.m_active_hash = util::hash(title) + 2;
    }
    else if (menu.window_ctx.m_active_hash == (util::hash(title) + 2)) {
        menu.draw_list.filled_rect(color_picker_position, alt_window_size, color_t(8, 8, 8, 255), 3.f);


        char color_buf[256]{ };

        sprintf(color_buf, "#%02X%02X%02X%02X",
            static_cast<uint8_t>(color.r * 255),
            static_cast<uint8_t>(color.g * 255),
            static_cast<uint8_t>(color.b * 255),
            static_cast<uint8_t>(color.a * 255));

        // set the color_buf string to clipboard...

        //for ( int idx = 0; idx < 2; idx++ ) {
        //    const bool hovered = menu.mouse_in_rect( color_picker_position + vec2_t( 0, 20 + ( idx * 20 ) ), color_picker_position + vec2_t( alt_window_size.x, 20 + ( idx * 20 ) + 19 ) );
        //    if ( hovered )
        //        menu.draw_list.filled_rect( color_picker_position + vec2_t( 0, 20 + ( idx * 20 ) ), vec2_t( alt_window_size.x, 20 ), color_t( 24, 24, 24, 255 ), 3.f );

        //    auto text_size = menu.drawing.calc_text_size( m_titles[ idx ] );

        //    if ( hovered && ( menu.mouse_active && !menu.old_mouse_active ) ) {
        //        if ( idx == 0 ) {
        //            // save color...
        //            printf( "%s\n", color_buf );
        //            auto len = strlen( color_buf );

        //            auto hdst = GlobalAlloc( GMEM_MOVEABLE | GMEM_DDESHARE, ( len + 1 ) * sizeof( char ) );
        //            if ( hdst ) {
        //                auto dst = ( LPSTR ) GlobalLock( hdst );
        //                if ( dst ) {
        //                    memcpy( dst, color_buf, len * sizeof( char ) );
        //                    dst[ len ] = '\0';
        //                }
        //            }
        //            GlobalUnlock( hdst );

        //            if ( OpenClipboard( nullptr ) ) {
        //                EmptyClipboard( );
        //                SetClipboardData( CF_TEXT, hdst );
        //                CloseClipboard( );
        //            }
        //        }
        //        else {
        //            if ( OpenClipboard( nullptr ) ) {
        //                if ( auto handle = GetClipboardData( CF_TEXT ) ) {
        //                    char* input = static_cast< char* >( GlobalLock( handle ) );
        //                    if ( input )
        //                        color = hex_to_rgb( input );

        //                    GlobalUnlock( handle );
        //                }

        //                CloseClipboard( );
        //            }
        //        }

        //        menu.window_ctx.m_active_hash = 0;
        //    }

        //    menu.draw_list.text( color_picker_position + vec2_t( 5, 20 + ( idx * 20 ) + 10 - text_size.y / 2 ), m_titles[ idx ], hovered ? globals::menu_accent : color_t( 60, 60, 60, 255 ), text_flags::text_flags_none );
        //}

        auto color_buf_size = menu.drawing.calc_text_size(color_buf);

        menu.draw_list.text(color_picker_position + vec2_t(5, 10 - (color_buf_size.y / 2)), color_buf, globals::palette::white, text_flags::text_flags_none);

        menu.draw_list.filled_rect(color_picker_position + vec2_t(alt_window_size.x - 15, 5), vec2_t(10, 10), color, 3.f);
        menu.draw_list.rect(color_picker_position + vec2_t(alt_window_size.x - 15, 5), vec2_t(10, 10), globals::palette::black, 3.f);

        menu.draw_list.rect(color_picker_position + vec2_t(1, 1), alt_window_size - vec2_t(2, 2), color_t(60, 60, 60, 255), 3.f);
        menu.draw_list.rect(color_picker_position, alt_window_size, globals::palette::black, 3.f);
    }
    else if (menu.window_ctx.m_active_hash == util::hash(title)) {
        auto color_hsv = color.to_hsv();

        menu.draw_list.filled_rect(color_picker_position, color_picker_size, color_t(8, 8, 8, 255), 3.f);

        menu.draw_list.rect(color_picker_position + vec2_t(1, 1), color_picker_size - vec2_t(2, 2), color_t(60, 60, 60, 255), 3.f);
        menu.draw_list.rect(color_picker_position, color_picker_size, globals::palette::black, 3.f);

        auto hue_bar_position = color_picker_position + vec2_t(color_picker_size.x - (15 + 5), 5);
        auto hue_bar_size = vec2_t(15, 152);

        for (int i{ }; i < 6; ++i) {
            menu.draw_list.multi_color_filled_rect(hue_bar_position + vec2_t(0, i * (hue_bar_size.y / 6.f)), vec2_t(hue_bar_size.x, hue_bar_size.y / 6.f), { hue_colors[i], hue_colors[i], hue_colors[i + 1], hue_colors[i + 1] });
        }

        menu.draw_list.rect(hue_bar_position, hue_bar_size, globals::palette::black);

        auto picker_position = color_picker_position + vec2_t(5, 5);
        auto picker_position_size = vec2_t(152, 152);

        auto picker_mouse_cursor = vec2_t(
            std::clamp(picker_position.x + Math::roundf(color_hsv.y * picker_position_size.x), picker_position.x, picker_position.x + picker_position_size.x),
            std::clamp(picker_position.y + Math::roundf((1.f - color_hsv.z) * picker_position_size.y), picker_position.y, picker_position.y + picker_position_size.y)
        );

        auto hue_bar_mouse_cursor = vec2_t(hue_bar_position.x, std::clamp(hue_bar_position.y + Math::roundf(color_hsv.x * hue_bar_size.y), hue_bar_position.y, hue_bar_position.y + hue_bar_size.y));

        // hue picker cursor
        menu.draw_list.rect(hue_bar_mouse_cursor - vec2_t(1, 1), vec2_t(hue_bar_size.x + 2, 7), globals::palette::black);
        menu.draw_list.rect(hue_bar_mouse_cursor + vec2_t(1, 1), vec2_t(hue_bar_size.x - 2, 3), globals::palette::black);
        menu.draw_list.rect(hue_bar_mouse_cursor, vec2_t(hue_bar_size.x, 5), globals::palette::white);

        auto hue_picker_hovered = menu.mouse_in_rect(hue_bar_position, hue_bar_position + hue_bar_size);
        if (hue_picker_hovered && menu.mouse_active) {
            hue_bar_mouse_cursor = vec2_t(hue_bar_position.x, std::clamp(menu.mouse_pos.y, hue_bar_position.y, hue_bar_position.y + hue_bar_size.y - 6));
            color_hsv.x = std::clamp(float(hue_bar_mouse_cursor.y - hue_bar_position.y) / float(hue_bar_size.y - 1), 0.0f, 0.99f);
        }

        auto main_picker_hovered = menu.mouse_in_rect(picker_position, picker_position + picker_position_size);
        if (main_picker_hovered && menu.mouse_active) {
            picker_mouse_cursor = vec2_t(
                std::clamp(menu.mouse_pos.x, picker_position.x + 2, picker_position.x + picker_position_size.x - 4),
                std::clamp(menu.mouse_pos.y, picker_position.y + 2, picker_position.y + picker_position_size.y - 4));

            color_hsv.y = std::clamp(float(picker_mouse_cursor.x - picker_position.x) / float(picker_position_size.x - 1), 0.0f, 1.0f);
            color_hsv.z = 1.0f - std::clamp(float(picker_mouse_cursor.y - picker_position.y) / float(picker_position_size.y - 1), 0.0f, 1.0f);
        }

        auto alpha_bar_position = vec2_t(color_picker_position.x + 5, color_picker_position.y + color_picker_size.y - 15);
        auto alpha_bar_size = vec2_t(color_picker_size.x - 28, 10);

        auto alpha_bar_mouse_cursor = vec2_t(alpha_bar_position.x + Math::roundf(color.a * alpha_bar_size.x), alpha_bar_position.y);

        color = color_t::hsv(color_hsv.x, color_hsv.y, color_hsv.z);

        auto picker_color = color_t::hsv(color_hsv.x, 1, 1);

        menu.draw_list.multi_color_filled_rect(picker_position, picker_position_size, { globals::palette::black, picker_color, picker_color, globals::palette::white });
        menu.draw_list.multi_color_filled_rect(picker_position, picker_position_size, { globals::palette::black.alpha(0), globals::palette::black.alpha(0), globals::palette::black, globals::palette::black });

        menu.draw_list.filled_rect(picker_mouse_cursor - vec2_t(1, 1), vec2_t(4, 4), globals::palette::white);
        menu.draw_list.rect(picker_mouse_cursor - vec2_t(1, 1), vec2_t(4, 4), globals::palette::black);

        menu.draw_list.rect(picker_position, picker_position_size, globals::palette::black);

        auto alpha_picker_hovered = menu.mouse_in_rect(alpha_bar_position, alpha_bar_position + alpha_bar_size);
        if (alpha_picker_hovered && menu.mouse_active) {
            alpha_bar_mouse_cursor = vec2_t(std::clamp(menu.mouse_pos.x, alpha_bar_position.x + 1, alpha_bar_position.x + alpha_bar_size.x - 5), alpha_bar_position.y);
        }

        color.a = std::clamp((alpha_bar_mouse_cursor.x - alpha_bar_position.x) / alpha_bar_size.x, 0.0f, 1.f);

        for (auto idx{ 0 }; idx < 30; idx++) {
            if (idx % 2 == 0) {
                menu.draw_list.filled_rect(vec2_t(alpha_bar_position.x + idx * 5 + 1, alpha_bar_position.y), vec2_t(5, 5), globals::palette::white);
                menu.draw_list.filled_rect(vec2_t(alpha_bar_position.x + idx * 5 + 1, alpha_bar_position.y + 5), vec2_t(5, 5), color_t(100, 100, 100, 255));
            }
            else {
                menu.draw_list.filled_rect(vec2_t(alpha_bar_position.x + idx * 5 + 1, alpha_bar_position.y), vec2_t(5, 5), color_t(100, 100, 100, 255));
                menu.draw_list.filled_rect(vec2_t(alpha_bar_position.x + idx * 5 + 1, alpha_bar_position.y + 5), vec2_t(5, 5), globals::palette::white);
            }
        }

        menu.draw_list.filled_rect(alpha_bar_position, alpha_bar_size, color);
        menu.draw_list.rect(alpha_bar_position, alpha_bar_size, color_t(0, 0, 0, 255), 0.f);

        menu.draw_list.rect(vec2_t(alpha_bar_mouse_cursor.x - 1, alpha_bar_mouse_cursor.y - 1), vec2_t(7, alpha_bar_size.y + 2), globals::palette::black);
        menu.draw_list.rect(vec2_t(alpha_bar_mouse_cursor.x + 1, alpha_bar_mouse_cursor.y + 1), vec2_t(3, alpha_bar_size.y - 2), globals::palette::black);
        menu.draw_list.rect(vec2_t(alpha_bar_mouse_cursor.x, alpha_bar_mouse_cursor.y), vec2_t(5, alpha_bar_size.y), globals::palette::white);
    }

    for (auto idx{ 0 }; idx < 4; idx++) {
        if (idx % 2 == 0) {
            menu.drawing.filled_rect(vec2_t(color_preview_position.x + idx * 5, color_preview_position.y), vec2_t(5, 5), globals::palette::white, 0.f);
            menu.drawing.filled_rect(vec2_t(color_preview_position.x + idx * 5, color_preview_position.y + 5), vec2_t(5, 5), color_t(100, 100, 100, 255), 0.f);
        }
        else {
            menu.drawing.filled_rect(vec2_t(color_preview_position.x + idx * 5, color_preview_position.y), vec2_t(5, 5), color_t(100, 100, 100, 255), 0.f);
            menu.drawing.filled_rect(vec2_t(color_preview_position.x + idx * 5, color_preview_position.y + 5), vec2_t(5, 5), globals::palette::white, 0.f);
        }
    }

    menu.drawing.multi_color_filled_rect(color_preview_position, color_preview_size, { color, color, color.darker(50), color.darker(50) });
    menu.drawing.rect(color_preview_position, color_preview_size, globals::palette::black, 0.f);

    if (!inlined) {
        auto text_position = menu.m_current_groupbox->cursor_position;

        menu.drawing.text(text_position, title, globals::palette::white, text_flags::text_flags_none);

        menu.m_current_groupbox->cursor_position.y += 16.f;
    }
}