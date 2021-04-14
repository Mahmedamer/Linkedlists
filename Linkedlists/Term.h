#pragma once

class Term
{
public:
	Term();
	Term(const Term& T)
	{
		coeff = T.coeff;
		power = T.power;
	}
	void operator = (const Term& T)
	{
		coeff = T.coeff;
		power = T.power;
	}
	Term(int, double);
	~Term();
	int getPower() const;
	double getCoeff() const;
	void setPower(int);
	void setCoef(double);
private:
	double coeff;
	int power;
};
Term::Term()
{
}
Term::Term(int p, double c)
{
	coeff = c;
	power = p;
}
Term::~Term()
{
}
int Term::getPower() const
{
	return power;
}
double Term::getCoeff() const
{
	return coeff;
}
void Term::setPower(int p)
{
	power = p;
}
void Term::setCoef(double c)
{
	coeff = c;
}