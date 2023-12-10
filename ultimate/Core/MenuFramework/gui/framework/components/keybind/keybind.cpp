#include "../../calliope.hpp"

void calliope::menu_t::components_t::keybind( const char* name, int& key, bool inlined ) {
    if ( !inlined ) { // todo finish this... poorly made design....
        auto button_position = menu.m_current_groupbox->cursor_position + vec2_t( 15, 5 );
        const auto button_size = vec2_t( 150, 20 );

        menu.drawing.filled_rect( button_position, button_size, color_t( 40, 40, 40, 255 ), 0.f );

        const bool in_use = menu.window_ctx.m_active_hash == util::hash( name );
        const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;
        
        auto code_name = AssemblyCSharp::KeyCodeEx::ToShortname((RustStructs::KeyCode)key, false);
        const auto codename_string = code_name->string_safe();


        auto label = codename_string.c_str() == XS("None") ? XS("unbound") : codename_string.c_str();

        if ( menu.mouse_in_rect( button_position, button_position + button_size ) && !in_use && was_empty_last_hash && ( menu.mouse_active && !menu.old_mouse_active ) ) {
            menu.window_ctx.m_active_hash = util::hash( name );
        }
        else if ( in_use ) {
            menu.drawing.filled_rect( button_position, button_size, globals::palette::white.alpha( 100 ), 0.f );

            label = XS("...");

            for ( int i{ }; i < 329; i++ ) {
                if ( util::is_key_pressed( i ) ) {
                    if (codename_string.c_str() != XS("None") )
                        key = i;

                    menu.window_ctx.m_active_hash = 0;
                }

                if ( util::is_key_pressed( RustStructs::Escape ) ) {
                    key = 0;
                    menu.window_ctx.m_active_hash = 0;
                }
            }
        }

        auto text_size = menu.drawing.calc_text_size( label );

        menu.drawing.text( vec2_t( button_position.x + ( button_size.x / 2 ) - ( text_size.x / 2 ), button_position.y + 3 ), label, globals::palette::white, text_flags::text_flags_style_dropshadow);
        menu.drawing.rect( button_position, button_size, color_t( 0, 0, 0, 255 ), 0.f );

        menu.m_current_groupbox->cursor_position.y += button_size.y + 10;
    }
    else {
        if ( !menu.m_current_groupbox )
            return;


        auto code_name = AssemblyCSharp::KeyCodeEx::ToShortname((RustStructs::KeyCode)key, false);
        const auto codename_string = code_name->string_safe();

        auto label_position = menu.m_current_groupbox->cursor_position + vec2_t( menu.m_current_groupbox->size.x - 24, -25 );

        const bool in_use = menu.window_ctx.m_active_hash == util::hash( name );
        const bool was_empty_last_hash = menu.window_ctx.m_last_hash == 0 && menu.window_ctx.m_active_hash == 0;

        auto label = codename_string.c_str() == XS("None") ? XS("...") : codename_string.c_str();
        auto label_size = menu.drawing.calc_text_size( label );

        auto bordered_label = XS("[") + std::string( label ) + XS("]");
        auto bordered_label_size = menu.drawing.calc_text_size( bordered_label.c_str( ) );

        label_position.x -= bordered_label_size.x;

        const bool hovered = menu.mouse_in_rect( label_position, label_position + bordered_label_size );

        if ( hovered && !in_use && was_empty_last_hash && ( menu.mouse_active && !menu.old_mouse_active ) ) {
            menu.window_ctx.m_active_hash = util::hash( name );
        }
        else if ( in_use ) {
            for ( int i{ }; i < 329; i++ ) {
                if ( util::is_key_pressed( i ) ) {
                    if (codename_string.c_str() != XS("None") )
                        key = i;

                    menu.window_ctx.m_active_hash = 0;
                }

                if ( util::is_key_pressed( RustStructs::Escape)) {
                    key = 0;
                    menu.window_ctx.m_active_hash = 0;
                }
            }
        }

        menu.drawing.text( label_position, bordered_label.c_str( ), in_use ? globals::menu_accent : ( hovered ? ( color_t( 160, 160, 160, 255 ) ) : color_t( 50, 50, 50, 255 ) ), text_flags::text_flags_style_dropshadow );
    }
}