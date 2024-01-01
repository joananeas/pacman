// Hecho por: Husnain Arsha, Ivan Aguilar y Joan Aneas :)

#include <iostream>
#include <string>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <Windows.h>
#include <conio.h>

using namespace std;


int jugar();
int menu();
int ancho = 1024;
int alto = 768;
const char* version = "v0.1.1"; // Tiene que ser const char* para que funcione con al_draw_text

ALLEGRO_DISPLAY* ventana;
ALLEGRO_FONT* hello_honey;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_TIMER* fps;
ALLEGRO_EVENT_QUEUE* event_queue;

void finalizar_allegro() {
	// Destruir el temporizador
	al_destroy_timer(segundoTimer);

	// Destruir la cola de eventos
	al_destroy_event_queue(event_queue);

	// Otros códigos de limpieza pueden ir aquí
}


int main() {
	if (!al_init()) {
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la librería Allegro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();

	ventana = al_create_display(ancho, alto);
	hello_honey = al_load_font("fuentes/hello_honey.otf", 70, 0);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);

	al_set_window_title(ventana, "Mi Juego");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);

	segundoTimer = al_create_timer(1.0);
	fps = al_create_timer(1.0 / 30);

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_install_keyboard();

	if (!al_install_keyboard()) {
		fprintf(stderr, "[Error] Inicialización del teclado.\n");
		return -1;
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(fps);
	al_start_timer(segundoTimer);

	menu();  // Aquí llamas a tu función de menú o cualquier otra función que tenga el bucle principal (jugar).

	al_destroy_display(ventana);
	al_destroy_timer(segundoTimer);
	al_destroy_timer(fps);
	al_destroy_event_queue(event_queue);
	al_destroy_font(hello_honey);

	return 0;
}

void dibujar_tablero() {
	ALLEGRO_COLOR colorPared = al_map_rgb(0, 0, 255); // Azul
	ALLEGRO_COLOR colorPasillo = al_map_rgb(0, 0, 0); // Negro

	// Dimensiones de la ventana
	int ventanaAncho = 1024;
	int ventanaAlto = 768;

	// Dimensiones del tablero
	int tableroAncho = 900;
	int tableroAlto = 600;

	// Calcular las coordenadas iniciales para centrar el tablero
	int inicioX = (ventanaAncho - tableroAncho) / 2; // 62
	int inicioY = (ventanaAlto - tableroAlto) / 2; // 84

	int dentroRectX = inicioX + 30; // contando grosor
	int dentroRectY = inicioY + 30;

	al_draw_filled_rectangle(inicioX, inicioY, inicioX + 900, inicioY + 30, colorPared); // Tope superior
	al_draw_filled_rectangle(inicioX + 840, inicioY, inicioX + 870, inicioY + 600, colorPared); // Tope derecha 
	al_draw_filled_rectangle(inicioX + 30, inicioY, inicioX + 60, inicioY + 600, colorPared); // Tope izquierdo
	al_draw_filled_rectangle(inicioX + 30, inicioY + 570, inicioX + 870, inicioY + 600, colorPared); // Tope inferior
	
	// Obstáculos

	// Lateral izquierda
	al_draw_filled_rectangle(dentroRectX + 90, dentroRectY + 60, dentroRectX + 210, dentroRectY + 120, colorPared); // 150 de ancho
	
	// Central superior
	al_draw_filled_rectangle(dentroRectX + 270, dentroRectY + 60, dentroRectX + 570, dentroRectY + 120, colorPared); // 300 de ancho

	// Lateral derecha
	al_draw_filled_rectangle(dentroRectX + 630, dentroRectY + 60, dentroRectX + 750, dentroRectY + 120, colorPared); // 150 de ancho

	// Lateral L izquierda
	al_draw_filled_rectangle(dentroRectX + 90, dentroRectY + 180, dentroRectX + 210, dentroRectY + 240, colorPared); // 150 de ancho
	al_draw_filled_rectangle(dentroRectX + 150, dentroRectY + 180, dentroRectX + 210, dentroRectY + 360, colorPared); // 180 de alto
	
	// Inferior izquierda
	al_draw_filled_rectangle(dentroRectX + 90, dentroRectY + 420, dentroRectX + 210, dentroRectY + 480, colorPared); // 60 de alto

	// Rectángulo central (fantasmas)
	al_draw_filled_rectangle(dentroRectX + 270, dentroRectY + 180, dentroRectX + 570, dentroRectY + 240, colorPared); // 60 de alto
	al_draw_filled_rectangle(dentroRectX + 270, dentroRectY + 180, dentroRectX + 330, dentroRectY + 360, colorPared); // 180 de alto
	al_draw_filled_rectangle(dentroRectX + 270, dentroRectY + 300, dentroRectX + 570, dentroRectY + 360, colorPared); // 60 de alto
	al_draw_filled_rectangle(dentroRectX + 510, dentroRectY + 180, dentroRectX + 570, dentroRectY + 360, colorPared); // 60 de alto

	// Lateral L derecha
	al_draw_filled_rectangle(dentroRectX + 630, dentroRectY + 180, dentroRectX + 750, dentroRectY + 240, colorPared); // 60 de alto
	al_draw_filled_rectangle(dentroRectX + 630, dentroRectY + 180, dentroRectX + 690, dentroRectY + 360, colorPared); // 180 de alto

	// Central inferior
	al_draw_filled_rectangle(dentroRectX + 270, dentroRectY + 420, dentroRectX + 570, dentroRectY + 480, colorPared); // 60 de alto

	// Inferior derecha
	al_draw_filled_rectangle(dentroRectX + 630, dentroRectY + 420, dentroRectX + 750, dentroRectY + 480, colorPared); // 60 de alto



	float grosor = 30;
	// Dibujar texto sobre el tablero
	ALLEGRO_FONT* font = al_create_builtin_font();
	if (!font) {
		fprintf(stderr, "Error al cargar la fuente incorporada.\n");
		return;
	}

	float puntos = 100;

	/*--------------------------------------------------------------------------------------------------------*/
	/**/al_draw_text(font, al_map_rgb(255, 255, 255), inicioX + 42, 50, ALLEGRO_ALIGN_CENTER, "Puntos: 10");/**/
	/**/al_draw_text(font, al_map_rgb(255, 255, 255), 512, 50, ALLEGRO_ALIGN_CENTER, "Vidas: 3");/*-----------*/
	/**/al_draw_text(font, al_map_rgb(255, 255, 255), inicioX + 875, 50, ALLEGRO_ALIGN_CENTER, version);/*----*/
	/*--------------------------------------------------------------------------------------------------------*/

	al_destroy_font(font);
}

int jugar() {
	ALLEGRO_DISPLAY* display = al_create_display(1024, 768);
	ALLEGRO_BITMAP* pacman = al_load_bitmap("../imagenes/sprites/pacman.png");

	if (!pacman) {
		printf("[ERROR] No se pudo cargar la imagen de pacman.\n");
		return -1;
	}
	// 11 * 17 (filas * columnas)
	// 1 es una pared, 0 es un pasillo
	// 2 es pacman, 3 es un fantasma
	// 4 son las pastillas, 5 es la fruta
	int tablero[11][17] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 0
		
		{1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1}, // 1
		{1, 0,1,1,1,0,1,1,1,1,1,0,1,1,1,0, 1}, // 2
		{1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1}, // 3
		{1, 0,1,1,1,0,1,1,1,1,1,0,1,1,1,0, 1}, // 4
		{1, 0,0,0,1,0,1,0,0,0,1,0,1,0,0,0, 1}, // 5
		{1, 0,0,0,1,0,1,1,1,1,1,0,1,0,0,0, 1}, // 6
		{1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1}, // 7
		{1, 0,1,1,1,0,1,1,1,1,1,0,1,1,1,0, 1}, // 8
		{1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1}, // 9

		{1,0,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1} // 10
	};

	

	if (!display) {
		printf("[ERROR] No se pudo crear la ventana.\n");
		return -1;
	}

	float posX = 500;
	float posY = 490;
	const char* tecla = "ninguna";
	ALLEGRO_FONT* font = al_create_builtin_font();

	printf("[MAIN] iniciando el juego...\n");

	while (true) {
		ALLEGRO_EVENT Evento;

		if (!event_queue) {
			printf("[ERROR] No se pudo crear la cola de eventos.\n");
			return -1;
		}

		al_wait_for_event(event_queue, &Evento);
		al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpia la pantalla a negro
		// Dibujar el tablero al estilo de Pac-Man
		dibujar_tablero();

		al_draw_bitmap(pacman, posX, posY, 0);

		
		al_draw_text(font, al_map_rgb(255, 255, 255), 500, 700, ALLEGRO_ALIGN_CENTER, "Tecla presionada: ");
		al_draw_text(font, al_map_rgb(255, 255, 255), 600, 700, ALLEGRO_ALIGN_CENTER, tecla);
		
		if (Evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (Evento.keyboard.keycode) {
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				printf("[MAIN] Arriba\n");
				posY -= 60;
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				printf("[MAIN] Abajo\n");
				posY += 60;
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				printf("[MAIN] Izquierda\n");
				posX -= 60;
				break;
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				printf("[MAIN] Derecha\n");
				posX += 60;
				break;
			default:
				break;
			}
		}

			// Controlar límites del tablero
			/*posX = (posX < 0) ? 0 : posX;
			posY = (posY < 0) ? 0 : posY;
			posX = (posX > ancho_tablero - ancho_pacman) ? (ancho_tablero - ancho_pacman) : posX;
			posY = (posY > alto_tablero - alto_pacman) ? (alto_tablero - alto_pacman) : posY;*/
		al_flip_display(); // Actualizar la pantalla
		al_rest(0.05);
	}
	al_destroy_display(display); // Liberar recursos al salir
	al_destroy_event_queue(event_queue);
	return 1;
}

int menu() {
	int segundos = 0;
	int x = -1, y = -1;
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR azar = al_map_rgb(255, 50, 65);

	ALLEGRO_BITMAP* menu_null = al_load_bitmap("imagenes/menu_null.png");
	ALLEGRO_BITMAP* menu_jugar = al_load_bitmap("imagenes/menu_jugar.png");
	ALLEGRO_BITMAP* menu_contadores = al_load_bitmap("imagenes/menu_contadores.png"); // La nueva opción @ivan
	ALLEGRO_BITMAP* menu_salir = al_load_bitmap("imagenes/menu_salir.png");

	//menu
	int botones[] = { 0 };

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);

		if (Evento.type == ALLEGRO_EVENT_TIMER) {
			if (Evento.timer.source == segundoTimer) {
				segundos++;
			}

		}
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (botones[0] == 0)
			al_draw_bitmap(menu_null, 0, 0, 0);
		else if (botones[0] == 1)
			al_draw_bitmap(menu_jugar, 0, 0, 0);
		else if (botones[0] == 3) // [ATENCION] Modificar este número si conviene
			al_draw_bitmap(menu_contadores, -4.5, 0, 0); // Muestra la imagen de contadores (hover)
		else
			al_draw_bitmap(menu_salir, 0, 0, 0);

		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			x = Evento.mouse.x;
			y = Evento.mouse.y;

			// Ancho de un botón: 475px | Alto de un botón: 180px

			if (x >= 490 && x <= 965 && y >= 80 && y <= 260) { // Coordenadas botón Jugar
				botones[0] = 1;
				if (Evento.mouse.button & 1)
					jugar();
			}
			else if (x >= 490 && x <= 965 && y >= 298 && y <= 467.8) {
				botones[0] = 3;
				if (Evento.mouse.button & 1)
					return 1;
				}
			else if (x >= 483 && x <= 965 && y >= 495 && y <= 681) {
				botones[0] = 2;
				if (Evento.mouse.button & 1)
					return 1;
			}
			else {
				botones[0] = 0;
			}


		}

		al_flip_display();
	}
	finalizar_allegro();

	return 0;
}