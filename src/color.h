#pragma once
class color
{
private:
	int cor;
	bool ativo;
public:
	color();
	color(const int c, const int at);
	~color();
	void set_cor(const int c) { this->cor = c; }
	const int get_cor()const { return cor; }

	void set_ativo(const int at) { this->ativo = at; }
	const bool get_ativo()const { return ativo; }

	void set_ambos(const int c, const int at) { this->cor = c; this->ativo = at; }

};

