#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

int displayResult1() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();  // Initialize the Allegro TTF addon
    ALLEGRO_DISPLAY* display = al_create_display(600, 600);

    // Load a TTF font with a specific size
    ALLEGRO_FONT* font = al_load_ttf_font("GORD.otf", 45, 0);

    if (!font) {
        fprintf(stderr, "Failed to load font.\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    
    al_install_audio();
	al_init_acodec_addon();
	al_reserve_samples(1);
	
	ALLEGRO_SAMPLE *song = al_load_sample("gameend.wav");
	ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	al_play_sample_instance(songInstance);

    const char* text = "PLAYER 1 WON";
    float textWidth = al_get_text_width(font, text);
    float textHeight = al_get_font_line_height(font);

    float x = (al_get_display_width(display) - textWidth) / 2;
    float y = (al_get_display_height(display) - textHeight) / 2;

    al_draw_text(font, al_map_rgb(125, 0, 125), x, y, 0, text);

    al_flip_display();
    al_rest(2.0);

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

    return 0;
}

int displayResult2() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();  // Initialize the Allegro TTF addon
    ALLEGRO_DISPLAY* display = al_create_display(600, 600);

    // Load a TTF font with a specific size
    ALLEGRO_FONT* font = al_load_ttf_font("GORD.otf", 45, 0);

    if (!font) {
        fprintf(stderr, "Failed to load font.\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    ALLEGRO_SAMPLE *song = al_load_sample("gameend.wav");
	ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	al_play_sample_instance(songInstance);

    const char* text = "PLAYER 2 WON";
    float textWidth = al_get_text_width(font, text);
    float textHeight = al_get_font_line_height(font);

    float x = (al_get_display_width(display) - textWidth) / 2;
    float y = (al_get_display_height(display) - textHeight) / 2;

    al_draw_text(font, al_map_rgb(125, 0, 125), x, y, 0, text);

    al_flip_display();
    al_rest(2.0);

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

    return 0;
}
	
	int displayResult3() {
    al_init();
    al_init_font_addon();
    al_init_ttf_addon();  // Initialize the Allegro TTF addon
    ALLEGRO_DISPLAY* display = al_create_display(600, 600);

    // Load a TTF font with a specific size
    ALLEGRO_FONT* font = al_load_ttf_font("GORD.otf", 45, 0);

    if (!font) {
        fprintf(stderr, "Failed to load font.\n");
        return -1;
    }

    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    ALLEGRO_SAMPLE *song = al_load_sample("draw.wav");
	ALLEGRO_SAMPLE_INSTANCE *songInstance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(songInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(songInstance, al_get_default_mixer());
	al_play_sample_instance(songInstance);

    const char* text = "IT'S A DRAW";
    float textWidth = al_get_text_width(font, text);
    float textHeight = al_get_font_line_height(font);

    float x = (al_get_display_width(display) - textWidth) / 2;
    float y = (al_get_display_height(display) - textHeight) / 2;

    al_draw_text(font, al_map_rgb(125, 0, 125), x, y, 0, text);

    al_flip_display();
    al_rest(2.0);

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_sample(song);
	al_destroy_sample_instance(songInstance);

    return 0;
}


