#pragma once

class pacman {
private:
	int vidas;
	int puntos;
	bool comerFantasmaActivo;
	float posX;
	float posY;
public:
	pacman(int _vidas, int _puntos, bool _comerFantasmaActivo, float _posX, float _posY) {
		vidas = _vidas;
		puntos = _puntos;
		posX = _posX;
		posY = _posY;
		comerFantasmaActivo = _comerFantasmaActivo;
	};

	void setVidas(int cantidad) { vidas -= cantidad; }
	int getVidas() { return vidas; }
	void setPuntos(int cantidad) { puntos += cantidad; }
	int getPuntos() { return puntos; }
	void setComerFantasmaActivo(bool _comerFantasmaActivo) { comerFantasmaActivo = _comerFantasmaActivo; }
	bool getComerFantasmaActivo() { return comerFantasmaActivo; }
	void setPosX(float _posX) { posX = _posX; }
	void setPosY(float _posY) { posY = _posY; }
	float getPosX() { return posX; }
	float getPosY() { return posY; }
};

class fantasma {
private:
	int nombre; // 1 = Blinky, 2 = Cherry
	bool comido;
	bool enCasa;
	float posX;
	float posY;
public:
	fantasma() {};

	fantasma(int _nombre, float _posX, float _posY, bool _comido, bool _enCasa) {
		nombre = _nombre;
		posX = _posX;
		posY = _posY;
		comido = _comido;
		enCasa = _enCasa;
	};

	void setComido() { comido = true; }
	bool getComido() { return comido; }
	void setEnCasa() { enCasa = false; }
	bool getEnCasa() { return enCasa; }
	void setPosX (float _posX) { posX = _posX; }
	void setPosY(float _posY) { posY = _posY; }
	float getPosX() { return posX; }
	float getPosY() { return posY; }

	int trayectoria(int nombreFantasma, int tablero[11][15], float posX, float posY) {
	// 1 = Blinky
	// 2 = Cherry
		switch (nombreFantasma) {
			case 1:
				// Blinky
				if (!enCasa) {
					
				}
				setEnCasa();
				break;
			case 2:
				// Cherry
				if (!enCasa) {
					
				}
				setEnCasa();
				break;
		}
		return 0;
	}
};