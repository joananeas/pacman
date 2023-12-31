// Joan Aneas 2024

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
#include "header.h"

using namespace std;

ALLEGRO_DISPLAY* ventana = NULL;
ALLEGRO_FONT* hello_honey = NULL;
ALLEGRO_TIMER* segundoTimer = NULL;
ALLEGRO_TIMER* fps = NULL;
ALLEGRO_EVENT_QUEUE* event_queue = NULL;
ALLEGRO_FONT* font = NULL;
ALLEGRO_TIMER* timerPowerUp = NULL;

int menu();
int ancho = 1024;
int alto = 768;
const char* version = "v0.2.4"; // Tiene que ser const char* para que funcione con al_draw_text

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
	fps = al_create_timer(1.0 / 60);
	timerPowerUp = al_create_timer(1.0);

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(timerPowerUp));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	
	bool kboard = al_is_keyboard_installed();
	printf("[INFO] Estado del teclado: %d\n", kboard);

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
	al_start_timer(timerPowerUp);
	al_start_timer(fps);
	al_start_timer(segundoTimer);
	

	menu(); 

	al_destroy_display(ventana);
	al_destroy_timer(segundoTimer);
	al_destroy_timer(fps);
	al_destroy_timer(timerPowerUp);
	al_destroy_event_queue(event_queue);
	al_destroy_font(hello_honey);

	return 0;
}

void dibujar_tablero(int frutasPastillasRecogidas[11][15], int puntos) {
	ALLEGRO_COLOR colorPared = al_map_rgb(0, 0, 255); // Azul
	ALLEGRO_COLOR colorPasillo = al_map_rgb(0, 0, 0); // Negro
	ALLEGRO_COLOR colorPastilla = al_map_rgb(255, 255, 255); // Blanco
	font = al_create_builtin_font();
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
	al_draw_filled_rectangle(dentroRectX + 360, dentroRectY + 180, dentroRectX + 480, dentroRectY + 240, al_map_rgb(255, 255, 50));
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

	// Pastillas horizontales
	/*---------------------------------------------------------------------------*/
	for (int i = 90; i < 850; i += 60) {
		if (frutasPastillasRecogidas[1][i / 60] == 4) {
			al_draw_filled_circle(inicioX + i, inicioY + 60, 4, colorPastilla);
		}
	}
	for (int i = 90; i < 850; i += 60) {
		if (frutasPastillasRecogidas[3][i / 60] == 4) {
			al_draw_filled_circle(inicioX + i, inicioY + 180, 4, colorPastilla);
		}
	}
	for (int i = 90; i < 850; i += 60) {
		if (frutasPastillasRecogidas[7][i / 60] == 4) {
			al_draw_filled_circle(inicioX + i, inicioY + 420, 4, colorPastilla);
		}
	}
	for (int i = 90; i < 850; i += 60) {
		if (frutasPastillasRecogidas[9][i / 60] == 4) {
			al_draw_filled_circle(inicioX + i, inicioY + 540, 4, colorPastilla);
		}
	}
	/*---------------------------------------------------------------------------*/

	// Pastillas verticales
	/*---------------------------------------------------------------------------*/
	for (int i = 60; i < 600; i += 60) {
		if (frutasPastillasRecogidas[i / 60][1] == 4) {
			al_draw_filled_circle(inicioX + 90, inicioY + i, 4, colorPastilla);
		}
	}
	for (int i = 60; i < 600; i += 60) {
		if (frutasPastillasRecogidas[i / 60][4] == 4) {
			al_draw_filled_circle(inicioX + 270, inicioY + i, 4, colorPastilla);
		}
	}
	for (int i = 60; i < 600; i += 60) {
		if (frutasPastillasRecogidas[i / 60][10] == 4) {
			al_draw_filled_circle(inicioX + 630, inicioY + i, 4, colorPastilla);
		}
	}
	for (int i = 60; i < 600; i += 60) {
		if (frutasPastillasRecogidas[i / 60][13] == 4) {
			al_draw_filled_circle(inicioX + 810, inicioY + i, 4, colorPastilla);
		}
	}
	/*---------------------------------------------------------------------------*/

	// Pastillas sueltas & Frutas
	/*---------------------------------------------------------------------------*/
	/*if (frutasPastillasRecogidas[1][1] == 4) {
		al_draw_filled_circle(inicioX + 150, inicioY + 360, 4, colorPastilla);
	}*/
	if(frutasPastillasRecogidas[6][12] == 4){
		al_draw_filled_circle(inicioX + 750, inicioY + 360, 4, colorPastilla);
	}
	if (frutasPastillasRecogidas[6][2] == 4) {
		al_draw_filled_circle(inicioX + 150, inicioY + 360, 4, colorPastilla);
	}

	al_draw_filled_circle(inicioX + 150, inicioY + 300, 10, colorPastilla); // Fruta L izquierda
	al_draw_filled_circle(inicioX + 750, inicioY + 300, 10, colorPastilla); // Fruta L derecha
	al_draw_filled_circle(inicioX + 90, inicioY + 60, 10, colorPastilla); // Fruta Arriba izquierda
	al_draw_filled_circle(inicioX + 810, inicioY + 60, 10, colorPastilla); // Fruta Arriba derecha
	al_draw_filled_circle(inicioX + 810, inicioY + 540, 10, colorPastilla); // Fruta Abajo derecha
	al_draw_filled_circle(inicioX + 90, inicioY + 540, 10, colorPastilla); // Fruta Abajo izquierda
	/*---------------------------------------------------------------------------*/

	float grosor = 30;
	// Dibujar texto sobre el tablero
	if (!font) {
		fprintf(stderr, "Error al cargar la fuente incorporada.\n");
		return;
	}

	const char * puntos_s;
	char buffer[20];
	sprintf_s(buffer, "%d", puntos);
	puntos_s = buffer;

	/*--------------------------------------------------------------------------------------------------------*/
	/**/al_draw_text(font, al_map_rgb(255, 255, 255), inicioX + 42, 50, ALLEGRO_ALIGN_CENTER, "Puntos: ");/**/
	/**/al_draw_text(font, al_map_rgb(255, 255, 255), inicioX + 92, 50, ALLEGRO_ALIGN_CENTER, puntos_s);/**/
	/**/al_draw_text(font, al_map_rgb(255, 255, 255), 512, 50, ALLEGRO_ALIGN_CENTER, "Vidas: 3");/*-----------*/
	/**/al_draw_text(font, al_map_rgb(255, 255, 255), inicioX + 875, 50, ALLEGRO_ALIGN_CENTER, version);/*----*/
	/*--------------------------------------------------------------------------------------------------------*/

	al_destroy_font(font);
}

string obtenerHoraActual() {
	time_t tiempoActual;
	time(&tiempoActual);
	struct tm tiempoLocal;
	localtime_s(&tiempoLocal, &tiempoActual);

	// Muestra la hora actual
	printf("[MAIN] Inicio de partida: %02d:%02d:%02d\n", tiempoLocal.tm_hour, tiempoLocal.tm_min, tiempoLocal.tm_sec);

	return to_string(tiempoLocal.tm_hour) + ":" + to_string(tiempoLocal.tm_min) + ":" + to_string(tiempoLocal.tm_sec);
}

void guardarFichero(string hora, int puntos) {
	FILE* fichero;

	if (fopen_s(&fichero, "../contadores.txt", "a") != 0) {
		printf("[ERROR] No se pudo abrir el fichero para añadir datos.\n");
		return;
	}
	else {
		fprintf(fichero, "\n");
		fprintf(fichero, "%s\t", hora.c_str());
		fprintf(fichero, "%d\t", puntos);
		fprintf(fichero, "%s\t", "true");
	}

	fclose(fichero);
}

string leerFichero() {
	FILE* fichero;
	if (fopen_s(&fichero, "../contadores.txt", "r") != 0) {
		printf("[ERROR] No se pudo abrir el fichero para leer datos.\n");
		return {};  // Devuelve un vector vacío en caso de error
	}

	string ficheroString;
	char buffer[100];
	while (fgets(buffer, 100, fichero) != NULL) {
		ficheroString += buffer;
	}

	fclose(fichero);
	return ficheroString;
}

int cantidadLineasFichero() {
	FILE* fichero;
	if (fopen_s(&fichero, "../contadores.txt", "r") != 0) {
		printf("[ERROR] No se pudo abrir el fichero para leer datos.\n");
		return -1;
	}

	char buffer[100];
	int lineas = 0;
	while (fgets(buffer, 100, fichero) != NULL) {
		lineas++;
	}

	fclose(fichero);
	return lineas;
}

int jugar() {
	ALLEGRO_DISPLAY* display = al_create_display(1024, 768);
	ALLEGRO_BITMAP* pacmanL = al_load_bitmap("../imagenes/sprites/pacman-l.png");
	ALLEGRO_BITMAP* pacmanR = al_load_bitmap("../imagenes/sprites/pacman-r.png");
	ALLEGRO_BITMAP* cherryL = al_load_bitmap("../imagenes/sprites/cherry-l.png");
	ALLEGRO_BITMAP* cherryR = al_load_bitmap("../imagenes/sprites/cherry-r.png");
	ALLEGRO_BITMAP* blinkyL = al_load_bitmap("../imagenes/sprites/blinky-l.png");
	ALLEGRO_BITMAP* blinkyR = al_load_bitmap("../imagenes/sprites/blinky-r.png");
	ALLEGRO_BITMAP* ghost = al_load_bitmap("../imagenes/sprites/ghost.png");
	ALLEGRO_BITMAP* ghostW = al_load_bitmap("../imagenes/sprites/ghost-w.png");
	ALLEGRO_FONT* font = al_create_builtin_font();

	int direccionActual = 0; // 0: Sin movimiento, 1: Arriba, 2: Abajo, 3: Izquierda, 4: Derecha
	int contador = 0;
	const char* tecla = "ninguna";
	float posX = 500;
	float posY = 490;

	float posCherryX = 440;
	float posCherryY = 360;
	float posBlinkyX = 560;
	float posBlinkyY = 360;

	int i = 7, j = 7;
	bool flag = true;
	bool powerUp = false;
	int posTab = 0;
	int puntos = 0;
	char orientacion = 'R';
	string horaActual = obtenerHoraActual();

	pacman comecocos(3, puntos, false, posX, posY); // Inicializamos que no está comido y que está en casa
	fantasma blinky(1, 560, 360, false, true); // Inicializamos que no está comido y que está en casa
	fantasma cherry(1, 440, 360, false, true); // Inicializamos que no está comido y que está en casa

	// 1 es una pared, 0 es un pasillo
	// 2 es pacman, 3 es un fantasma
	// 4 son las pastillas, 5 es la fruta
	// 6 es que los fantasmas estan encima
	// 7 es blinky
	// 8 es cherry

	int tablero[11][15] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 0
		{1,5,4,4,4,4,4,4,4,4,4,4,4,5,1}, // 1
		{1,4,1,1,4,1,1,1,1,1,4,1,1,4,1}, // 2
		{1,4,4,4,4,4,4,4,4,4,4,4,4,4,1}, // 3
		{1,4,1,1,4,1,1,1,1,1,4,1,1,4,1}, // 4
		{1,4,5,1,4,1,3,0,3,1,4,1,5,4,1}, // 5
		{1,4,4,1,4,1,1,1,1,1,4,1,4,4,1}, // 6
		{1,4,4,4,4,4,4,4,4,4,4,4,4,4,1}, // 7
		{1,4,1,1,4,1,1,1,1,1,4,1,1,4,1}, // 8
		{1,5,4,4,4,4,4,4,4,4,4,4,4,5,1}, // 9
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} // 10
	};

	if (!display) {
		printf("[ERROR] No se pudo crear la ventana.\n");
		return -1;
	}
	
	printf("[INFO] Tablero[%d][%d] = %d\n", i, j, tablero[i][j]);
	printf("[MAIN] iniciando el juego...\n");
	

	while (flag) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		if (!event_queue) {
			printf("[ERROR] No se pudo crear la cola de eventos.\n");
			return -1;
		}
		/*-----------------------------*/
		// Inicialización
			blinky.setPosX(posBlinkyX);
			blinky.setPosY(posBlinkyY);
			cherry.setPosX(posCherryX);
			cherry.setPosY(posCherryY);
		/*-----------------------------*/
		al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpia la pantalla a negro
		// Dibujar el tablero al estilo de Pac-Man
		dibujar_tablero(tablero, comecocos.getPuntos());
		

		if(orientacion == 'L') al_draw_bitmap(pacmanL, comecocos.getPosX(), comecocos.getPosY(), 0);
		else al_draw_bitmap(pacmanR, comecocos.getPosX(), comecocos.getPosY(), 0);

		blinky.trayectoria(1, tablero, posBlinkyX, posBlinkyY);
		cherry.trayectoria(2, tablero, posCherryX, posCherryY);

		if (powerUp == true && contador < 11) {
			if (contador % 2 == 0) {
				al_draw_bitmap(ghostW, cherry.getPosX(), cherry.getPosY(), 0);
				al_draw_bitmap(ghostW, blinky.getPosX(), blinky.getPosY(), 0);
			}
			else {
				al_draw_bitmap(ghost, cherry.getPosX(), cherry.getPosY(), 0);
				al_draw_bitmap(ghost, blinky.getPosX(), blinky.getPosY(), 0);
			}
		}
		else {
			powerUp = false;
			al_draw_bitmap(cherryL, cherry.getPosX(), cherry.getPosY(), 0);
			al_draw_bitmap(blinkyR, blinky.getPosX(), blinky.getPosY(), 0);
		}

		al_draw_text(font, al_map_rgb(255, 255, 255), 500, 700, ALLEGRO_ALIGN_CENTER, "Tecla presionada: ");
		al_draw_text(font, al_map_rgb(255, 255, 255), 600, 700, ALLEGRO_ALIGN_CENTER, tecla);

		if (Evento.type == ALLEGRO_EVENT_TIMER) {
			//printf("[INFO] Evento timer");
			if (Evento.timer.source == timerPowerUp) {
				contador++; // Incrementar el contador en cada pulsación del temporizador
				printf("[INFO] Contador: %d\n", contador);
			}
		}

		switch (Evento.type) {
			printf("[INFO] Tipo de evento: %d", Evento.type);
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (Evento.keyboard.keycode) {
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				printf("[MAIN] Arriba\n");
				if (tablero[i - 1][j] == 0 || tablero[i - 1][j] == 4 || tablero[i - 1][j] == 5) {			
					posTab = tablero[i - 1][j];
					tablero[i - 1][j] = 0;
					posY -= 60;
					comecocos.setPosY(posY);
					i--;
					if (posTab == 4) comecocos.setPuntos(100);
					else if (posTab == 5) { 
						comecocos.setPuntos(500);
						powerUp = true;
						contador = 0;
					};
					printf("[INFO] Tablero[%d][%d] = %d\n", i, j, tablero[i][j]);
					printf("[INFO] Moviendo hacia la izquierda.\n");
				}
				tecla = "arriba";
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				printf("[MAIN] Abajo\n");
				if (tablero[i + 1][j] == 0 || tablero[i + 1][j] == 4 || tablero[i + 1][j] == 5) {
					posTab = tablero[i + 1][j];
					tablero[i + 1][j] = 0;
					posY += 60;
					comecocos.setPosY(posY);
					i++;
					if (posTab == 4) comecocos.setPuntos(100);
					else if (posTab == 5) {
						comecocos.setPuntos(500);
						powerUp = true;
						contador = 0;
					};
					printf("[INFO] Tablero[%d][%d] = %d\n", i, j, tablero[i][j]);
					printf("[INFO] Moviendo hacia la derecha.\n");
				}
				tecla = "abajo";
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				printf("[MAIN] Izquierda\n");
				if (tablero[i][j - 1] == 0 || tablero[i][j - 1] == 4 || tablero[i][j - 1] == 5) {
					posTab = tablero[i][j - 1];
					tablero[i][j - 1] = 0;
					orientacion = 'L';
					posX -= 60;
					comecocos.setPosX(posX);
					j--;
					if (posTab == 4) comecocos.setPuntos(100);
					else if (posTab == 5) {
						comecocos.setPuntos(500);
						powerUp = true;
						contador = 0;
					};
					printf("[INFO] Tablero[%d][%d] = %d\n", i, j, tablero[i][j]);
					printf("[INFO] Moviendo hacia arriba.\n");
				}
				tecla = "izquierda";
				break;
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				printf("[MAIN] Derecha\n");
				if (tablero[i][j + 1] == 0 || tablero[i][j + 1] == 4 || tablero[i][j + 1] == 5) {
					posTab = tablero[i][j + 1];
					tablero[i][j + 1] = 0;
					orientacion = 'R';
					posX += 60;
					comecocos.setPosX(posX);
					j++;
					if (posTab == 4) comecocos.setPuntos(100);
					else if (posTab == 5) {
						comecocos.setPuntos(500);
						powerUp = true;
						contador = 0;
					};
					printf("[INFO] Tablero[%d][%d] = %d\n", i, j, tablero[i][j]);
					printf("[INFO] Moviendo hacia abajo.\n");
				}
				tecla = "derecha";
				break;
			case ALLEGRO_KEY_ESCAPE:
				printf("[MAIN] Saliendo del juego...\n");
				guardarFichero(horaActual, puntos);
				al_destroy_bitmap(pacmanR);
				al_destroy_bitmap(pacmanL);
				al_destroy_display(display); // Liberar recursos al salir
				al_destroy_event_queue(event_queue);
				flag = false;
				break;
			default:
				break;
			}
			break;
		case ALLEGRO_EVENT_KEY_UP:
			break;
		default:
			break;
		}

		const float distanciaObjetivo = 60.0; // ajusta esto a la distancia deseada en píxeles
		int valTablero = tablero[i][j];
		
		al_flip_display(); // Actualizar la pantalla
		//posX += mov * velocidad * deltaTime;
		//double deltaTime = al_get_timer_count(fps);
	}
	return 1;
}

int contadores() {
	ALLEGRO_COLOR colorPastilla = al_map_rgb(255, 255, 255); // Blanco
	font = al_create_builtin_font();

	printf("[INFO] Iniciando contadores...\n");
	int lineas = cantidadLineasFichero();
	printf("[INFO] Cantidad de líneas: %d\n", lineas);
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

	bool flag = true;
	string fich = leerFichero();
	printf("[INFO] Fichero: \n%s", fich.c_str());

	while (true) {
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		if (!event_queue) {
			printf("[ERROR] No se pudo crear la cola de eventos.\n");
			return -1;
		}

		al_clear_to_color(al_map_rgb(0, 0, 0)); // Limpia la pantalla a negro
		al_draw_filled_rectangle(inicioX, inicioY, inicioX + 900, inicioY + 10, colorPastilla);
		al_draw_filled_rectangle(inicioX, inicioY + 30, inicioX + 900, inicioY + 33, colorPastilla);
		al_draw_filled_rectangle(inicioX, inicioY, inicioX + 10, inicioY + 30, colorPastilla);
		al_draw_filled_rectangle(inicioX + 890, inicioY + 10, inicioX + 900, inicioY + 30, colorPastilla);

		al_draw_textf(font, al_map_rgb(255, 255, 255), inicioX + 450, 50, ALLEGRO_ALIGN_CENTER, "%s", "[CONTADORES]");
		al_draw_textf(font, al_map_rgb(255, 255, 255), inicioX + 150, inicioY + 18, ALLEGRO_ALIGN_CENTER, "%s", "Partida");
		al_draw_textf(font, al_map_rgb(255, 255, 255), inicioX + 450, inicioY + 18, ALLEGRO_ALIGN_CENTER, "%s", "Puntos");
		al_draw_textf(font, al_map_rgb(255, 255, 255), inicioX + 750, inicioY + 18, ALLEGRO_ALIGN_CENTER, "%s", "Estado");


		al_draw_textf(font, al_map_rgb(255, 255, 255), inicioX + 150, inicioY + 18 + (25), ALLEGRO_ALIGN_CENTER, "%s", fich.c_str());
		//j++;

		al_flip_display();
	}
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
				if (Evento.mouse.button & 1) contadores();
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