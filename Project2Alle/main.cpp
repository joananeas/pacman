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
const char* version = "v0.1.2"; // Tiene que ser const char* para que funcione con al_draw_text

ALLEGRO_DISPLAY* ventana = NULL;
ALLEGRO_FONT* hello_honey = NULL;
ALLEGRO_TIMER* segundoTimer = NULL;
ALLEGRO_TIMER* fps = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;

static void finalizar_allegro() {
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
	al_install_keyboard();
	al_init_image_addon();

	//al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

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

	if (!al_install_keyboard()) {
		printf("[Error] Inicialización del teclado.\n");
		return -1;
	}

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(fps);
	al_start_timer(segundoTimer);

	menu(); 

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
	ALLEGRO_COLOR colorPastilla = al_map_rgb(255, 255, 255); // Blanco

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
	
	// Pastillas horizontales
	/*---------------------------------------------------------------------------*/
	/**/for (int i = 90; i < 850; i += 60) {
	/**/	al_draw_filled_circle(inicioX + i, inicioY + 60, 4, colorPastilla);
	/**/}
	/**/for (int i = 90; i < 850; i += 60) {
	/**/	al_draw_filled_circle(inicioX + i, inicioY + 180, 4, colorPastilla);
	/**/}
	/**/for (int i = 90; i < 850; i += 60) {
	/**/	al_draw_filled_circle(inicioX + i, inicioY + 420, 4, colorPastilla);
	/**/}
	/**/for (int i = 90; i < 850; i += 60) {
	/**/	al_draw_filled_circle(inicioX + i, inicioY + 540, 4, colorPastilla);
	/**/}
	/*---------------------------------------------------------------------------*/
	
	// Pastillas verticales
	/*---------------------------------------------------------------------------*/
	/**/for (int i = 60; i < 600; i += 60) {
	/**/	al_draw_filled_circle(inicioX + 90, inicioY + i, 4, colorPastilla);
	/**/}
	/**/for (int i = 60; i < 600; i += 60) {
	/**/	al_draw_filled_circle(inicioX + 270, inicioY + i, 4, colorPastilla);
	/**/}
	/**/for (int i = 60; i < 600; i += 60) {
	/**/	al_draw_filled_circle(inicioX + 630, inicioY + i, 4, colorPastilla);
	/**/}
	/**/for (int i = 60; i < 600; i += 60) {
	/**/	al_draw_filled_circle(inicioX + 810, inicioY + i, 4, colorPastilla);
	/**/}
	/*---------------------------------------------------------------------------*/

	// Pastillas sueltas & Frutas
	/*---------------------------------------------------------------------------*/
	/**/al_draw_filled_circle(inicioX + 150, inicioY + 300, 10, colorPastilla); // Fruta L izquierda
	/**/al_draw_filled_circle(inicioX + 150, inicioY + 360, 4, colorPastilla);
	/**/al_draw_filled_circle(inicioX + 750, inicioY + 300, 10, colorPastilla); // Fruta L derecha
	/**/al_draw_filled_circle(inicioX + 750, inicioY + 360, 4, colorPastilla);
	/**/al_draw_filled_circle(inicioX + 90, inicioY + 60, 10, colorPastilla); // Fruta Arriba izquierda
	/**/al_draw_filled_circle(inicioX + 810, inicioY + 60, 10, colorPastilla); // Fruta Arriba derecha
	/**/al_draw_filled_circle(inicioX + 810, inicioY + 540, 10, colorPastilla); // Fruta Abajo derecha
	/**/al_draw_filled_circle(inicioX + 90, inicioY + 540, 10, colorPastilla); // Fruta Abajo izquierda
	/*---------------------------------------------------------------------------*/

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

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} // 10
	};

	if (!display) {
		printf("[ERROR] No se pudo crear la ventana.\n");
		return -1;
	}

	float posX = 500;
	float posY = 490;
	const char* tecla = "ninguna";
	bool flag = true;
	ALLEGRO_FONT* font = al_create_builtin_font();

	printf("[MAIN] iniciando el juego...\n");
	int direccionActual = 0; // 0: Sin movimiento, 1: Arriba, 2: Abajo, 3: Izquierda, 4: Derecha

	while (flag) {
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
		//printf("[INFO] Tipo de evento: %d", Evento.type);
		//printf("[INFO] Tecla: %s\n", al_keycode_to_name(Evento.keyboard.keycode));		
		/*if (Evento.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("[INFO] Tecla presionada.\n");
			switch (Evento.keyboard.keycode) {
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				printf("[MAIN] Arriba\n");
				direccionActual = 1;
				tecla = "arriba";
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				printf("[MAIN] Abajo\n");
				direccionActual = 2;
				tecla = "abajo";
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				printf("[MAIN] Izquierda\n");
				direccionActual = 3;
				tecla = "izquierda";
				break;
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				printf("[MAIN] Derecha\n");
				direccionActual = 4;
				tecla = "derecha";
				break;
			case ALLEGRO_KEY_ESCAPE:
				printf("[MAIN] Saliendo del juego...\n");
				flag = false;
				break;
			default:
				break;
			}
		}*/
		switch (Evento.type) {
			printf("[INFO] Tipo de evento: %d", Evento.type);
			case ALLEGRO_EVENT_KEY_DOWN:
				switch (Evento.keyboard.keycode) {
					case ALLEGRO_KEY_W:
					case ALLEGRO_KEY_UP:
						printf("[MAIN] Arriba\n");
						direccionActual = 1;
						tecla = "arriba";
						break;
					case ALLEGRO_KEY_S:
					case ALLEGRO_KEY_DOWN:
						printf("[MAIN] Abajo\n");
						direccionActual = 2;
						tecla = "abajo";
						break;
					case ALLEGRO_KEY_A:
					case ALLEGRO_KEY_LEFT:
						printf("[MAIN] Izquierda\n");
						direccionActual = 3;
						tecla = "izquierda";
						break;
					case ALLEGRO_KEY_D:
					case ALLEGRO_KEY_RIGHT:
						printf("[MAIN] Derecha\n");
						direccionActual = 4;
						tecla = "derecha";
						break;
					case ALLEGRO_KEY_ESCAPE:
						printf("[MAIN] Saliendo del juego...\n");
						flag = false;
						break;
					default:
						break;
				}
				break;
			case ALLEGRO_EVENT_KEY_UP:
				printf("[INFO] Tecla levantada.\n");
				break;
			default:
				break;
		}	

		if (Evento.type == ALLEGRO_EVENT_KEY_UP) {
			printf("[INFO] Tecla levantada.\n");
		}

		// Mueve la posición en la dirección actual
		switch (direccionActual) {
			case 1:
				posY -= 60;
				break;
			case 2:
				posY += 60;
				break;
			case 3:
				posX -= 60;
				break;
			case 4:
				posX += 60;
				break;
			default:
				break;
		}

			// Controlar límites del tablero
			/*posX = (posX < 0) ? 0 : posX;
			posY = (posY < 0) ? 0 : posY;
			posX = (posX > ancho_tablero - ancho_pacman) ? (ancho_tablero - ancho_pacman) : posX;
			posY = (posY > alto_tablero - alto_pacman) ? (alto_tablero - alto_pacman) : posY;*/
		al_flip_display(); // Actualizar la pantalla
		al_rest(0.5);
	}
	al_destroy_bitmap(pacman);
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
	int botones = 0;

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);

		if (Evento.type == ALLEGRO_EVENT_TIMER && Evento.timer.source == segundoTimer) {
			segundos++;
		}

		al_clear_to_color(al_map_rgb(0, 0, 0));

		switch (botones)
		{
			default:
			case 0:
				al_draw_bitmap(menu_null, 0, 0, 0);
				break;
			case 1:
				al_draw_bitmap(menu_jugar, 0, 0, 0);
				break;
			case 2:
				al_draw_bitmap(menu_contadores, -4.5, 0, 0);
				break;
			case 3:
				al_draw_bitmap(menu_salir, 0, 0, 0);
				break;
		}

		// Ancho de un botón: 475px | Alto de un botón: 180px
		int botonJugar = (x >= 490 && x <= 965 && y >= 80 && y <= 260);
		int botonContadores = (x >= 490 && x <= 965 && y >= 298 && y <= 467.8);
		int botonSalir = (x >= 483 && x <= 965 && y >= 495 && y <= 681);

		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			x = Evento.mouse.x;
			y = Evento.mouse.y;

			if (botonJugar) { 
				botones = 1; 
				if (Evento.mouse.button & 1) jugar();
			}
			else if (botonContadores) { 
				botones = 2; 
				if (Evento.mouse.button & 1) return 1;
			}
			else if (botonSalir) { 
				botones = 3; 
				if (Evento.mouse.button & 1) return 1;
			}
			else botones = 0;
		}
		al_flip_display();
	}
	finalizar_allegro();

	return 0;
}