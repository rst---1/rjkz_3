#include <deal.II/base/quadrature_lib.h>
#include <deal.II/base/function.h>
#include <deal.II/base/logstream.h>
#include <deal.II/lac/vector.h>
#include <deal.II/lac/full_matrix.h>
#include <deal.II/lac/sparse_matrix.h>
#include <deal.II/lac/compressed_sparsity_pattern.h>
#include <deal.II/lac/solver_cg.h>
#include <deal.II/lac/precondition.h>
#include <deal.II/grid/tria.h>
#include <deal.II/dofs/dof_handler.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/tria_boundary_lib.h>
#include <deal.II/dofs/dof_tools.h>
#include <deal.II/dofs/dof_accessor.h>
#include <deal.II/fe/fe_values.h>
#include <deal.II/numerics/vector_tools.h>
#include <deal.II/numerics/matrix_tools.h>
#include <deal.II/numerics/data_out.h>
#include <fstream>
#include <iostream>
#include <deal.II/fe/fe_q.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/lac/constraint_matrix.h>
#include <deal.II/grid/grid_refinement.h>
#include <deal.II/numerics/error_estimator.h>
#include <deal.II/grid/grid_tools.h>											//для gmsh
#include <deal.II/grid/grid_in.h>												//для gmsh
#include <map>																	//для gmsh

using namespace dealii;

int NumberOfProblem=4;															//1-трёхслойная плита 1 к 10
																				//2-трёхслойная плита 1 к 5
																				//3-трёхслойная балка 1 к 1
																				//4-однослойная балка 1 к 1
																				//5-однослойная плита 1 к 5
																				//6-однослойная плита 1 к 10

double	E_z1 = 10.0,															//модуль Юнга
		E_z2 = 1.0,
		E_z3 = 10.0,
		nui = 0.25,																//коэффициент Пуассона
		integral = 0.0,															//для расчёта интеграла по поверхности функции U_z (постоянная C)
		width = 6.772726;														//ширина балки
double Pi = 3.14159265358;
int N = 6;																		//количество рефайнов

template <int dim>
class Mu_zx : public Function<dim>
{
  public:
    Mu_zx () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double Mu_zx<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const		//задание анизотропного коэффициента Mu_zx
{
  switch( NumberOfProblem ) {
   case 1:
       if(p(0)<=-0.5/3)	{return E_z1/(2.0*(1.0+nui));}
			else	if(p(0)<=0.5/3)	{return E_z2/(2.0*(1.0+nui));}
			else	{return E_z3/(2.0*(1.0+nui));}
       break;
   case 2:
       if(p(0)<=-0.5/3)	{return E_z1/(2.0*(1.0+nui));}
			else	if(p(0)<=0.5/3)	{return E_z2/(2.0*(1.0+nui));}
			else	{return E_z3/(2.0*(1.0+nui));}
       break;
   case 3:
       if(p(0)<=-0.5/3)	{return E_z1/(2.0*(1.0+nui));}
			else	if(p(0)<=0.5/3)	{return E_z2/(2.0*(1.0+nui));}
			else	{return E_z3/(2.0*(1.0+nui));}
       break;
   case 4:
       return E_z2/(2.0*(1.0+nui));
       break;
   case 5:
       return E_z2/(2.0*(1.0+nui));
       break;
   case 6:
       return E_z2/(2.0*(1.0+nui));
       break;} 
}
//------------------------------------------------------------------------------
template <int dim>
class Mu_zy : public Function<dim>
{
  public:
    Mu_zy () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double Mu_zy<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const		//задание анизотропного коэффициента Mu_zy
{
  switch( NumberOfProblem ) {
   case 1:
       if(p(0)<=-0.5/3)	{return E_z1/(2.0*(1.0+nui));}
			else	if(p(0)<=0.5/3)	{return E_z2/(2.0*(1.0+nui));}
			else	{return E_z3/(2.0*(1.0+nui));}
       break;
   case 2:
       if(p(0)<=-0.5/3)	{return E_z1/(2.0*(1.0+nui));}
			else	if(p(0)<=0.5/3)	{return E_z2/(2.0*(1.0+nui));}
			else	{return E_z3/(2.0*(1.0+nui));}
       break;
   case 3:
       if(p(0)<=-0.5/3)	{return E_z1/(2.0*(1.0+nui));}
			else	if(p(0)<=0.5/3)	{return E_z2/(2.0*(1.0+nui));}
			else	{return E_z3/(2.0*(1.0+nui));}
       break;
   case 4:
       return E_z2/(2.0*(1.0+nui));
       break;
   case 5:
       return E_z2/(2.0*(1.0+nui));
       break;
   case 6:
       return E_z2/(2.0*(1.0+nui));
       break;}
}


const Mu_zx<2> mu_zx;                                                           //объявление объектов
const Mu_zy<2> mu_zy;


//------------------------------------------------------------------------------
template <int dim>
class Tau_zz : public Function<dim>
{
  public:
    Tau_zz () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double Tau_zz<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задание функции Mu_zz
	
  switch( NumberOfProblem ) {
   case 1:
       if(p(0)<=-0.5/3) {return -E_z1*p(0);}
			else if(p(0)<=0.5/3) {return -E_z2*p(0);}
			else {return -E_z3*p(0);}
       break;
   case 2:
       if(p(0)<=-0.5/3) {return -E_z1*p(0);}
			else if(p(0)<=0.5/3) {return -E_z2*p(0);}
			else {return -E_z3*p(0);}
       break;
   case 3:
       if(p(0)<=-0.5/3) {return -E_z1*p(0);}
			else if(p(0)<=0.5/3) {return -E_z2*p(0);}
			else {return -E_z3*p(0);}
       break;
   case 4:
       return -E_z2*p(0);
	   break;
   case 5:
       return -E_z2*p(0);
       break;
   case 6:
       return -E_z2*p(0);
       break;}
}
//------------------------------------------------------------------------------
template <int dim>
class U_x : public Function<dim>
{
  public:
    U_x () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
    virtual double mygradient (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double U_x<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задание функции U_x
	double b = width;																//общий вид формулы
	double C0 = 0.5;
	double C1 = 1.0 / 12 + C0 * C0 - b * b / 3;
	return (   nui/2 * ( p(0)*p(0) - p(1)*p(1) + C1 )   );
	
//	return (   nui/2 * ( p(0)*p(0) - p(1)*p(1) )  );
}
template <int dim>
double U_x<dim>::mygradient (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задание производной функции U_x
    return 0;						//тест2
}
//------------------------------------------------------------------------------
template <int dim>
class U_y : public Function<dim>
{
  public:
    U_y () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
    virtual double mygradient (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double U_y<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задание функции U_y
//	return 0;
	return nui*p(0)*p(1);
//	return nui*(p(0)-0.5)*p(1);
}
template <int dim>
double U_y<dim>::mygradient (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задание производной функции U_y
	return 0;
}
//------------------------------------------------------------------------------
template <int dim>
class FunctionAnalisys : public Function<dim>
{
  public:
    FunctionAnalisys () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
	virtual double mygradientX (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
	virtual double mygradientY (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double FunctionAnalisys<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{
	double h=0.5/3;
	double C_1 = 0.51;
	double U_z1_original, U_z1_slagaemoe, U_z2_original, U_z2_slagaemoe, U_z3;
	double ch, ch_, sh, sh_, Summ;
	double b = 1.0, drob = 0.0;
	double C0 = 0.0, c0 = 0.0;
	
  switch( NumberOfProblem ) {
   case 1:
			U_z1_original = -1.0/12 - nui/12 - p(0)/4 - 5.0*nui*p(0)/24 + p(0)*p(0)*p(0)/3 + nui*p(0)*p(0)*p(0)/6;
			U_z1_slagaemoe = -1.0/12 - h/4 + h*h*h/3 - nui/12 - 5.0*h*nui/24 + nui*h*h*h/6;
			U_z2_original = -E_z1*h/4/E_z2 - 2.0*h*h*h/3 + E_z1*h*h*h/E_z2 + h*nui/24 - E_z1*h*nui/4/E_z2
					- 5.0*h*h*h*nui/6 + E_z1*h*h*h*nui/E_z2 - E_z1*p(0)/4/E_z2 - h*h*p(0) + E_z1*h*h*p(0)/E_z2
					+ nui*p(0)/24 - E_z1*nui*p(0)/4/E_z2 - h*h*nui*p(0) + E_z1*h*h*nui*p(0) + p(0)*p(0)*p(0)/3
					+ nui*p(0)*p(0)*p(0)/6;
			U_z2_slagaemoe = -E_z1*h/2/E_z2 - 4.0*h*h*h/3 + 2.0*E_z1*h*h*h/E_z2 + h*nui/12 - E_z1*h*nui/2/E_z2
					- 5.0*h*h*h*nui/3 + 2.0*E_z1*h*h*h*nui/E_z2;
			U_z3 = E_z1*h/4/E_z3 + 2.0*h*h*h/3 - E_z1*h*h*h/E_z3 - h*nui/24 - E_z1*h*nui/4/E_z3
					+ 5.0*h*h*h*nui/6 - E_z1*h*h*h*nui/E_z2 - E_z1*p(0)/4/E_z3 - h*h*p(0) + E_z1*h*h*p(0)/E_z3
					+ nui*p(0)/24 - E_z1*nui*p(0)/4/E_z3 - h*h*nui*p(0) + E_z1*h*h*nui*p(0)/E_z3
					+ p(0)*p(0)*p(0)/3 + p(0)*p(0)*p(0)*nui/6;
			if(p(0)<=-h) {return U_z1_original + C_1;}
			else if(p(0)<h) {return U_z1_slagaemoe + U_z2_original + C_1;}
			else {return U_z1_slagaemoe + U_z2_slagaemoe + U_z3 + C_1;}
       break;
   case 2:
			U_z1_original = -1.0/12 - nui/12 - p(0)/4 - 5.0*nui*p(0)/24 + p(0)*p(0)*p(0)/3 + nui*p(0)*p(0)*p(0)/6;
			U_z1_slagaemoe = -1.0/12 - h/4 + h*h*h/3 - nui/12 - 5.0*h*nui/24 + nui*h*h*h/6;
			U_z2_original = -E_z1*h/4/E_z2 - 2.0*h*h*h/3 + E_z1*h*h*h/E_z2 + h*nui/24 - E_z1*h*nui/4/E_z2
					- 5.0*h*h*h*nui/6 + E_z1*h*h*h*nui/E_z2 - E_z1*p(0)/4/E_z2 - h*h*p(0) + E_z1*h*h*p(0)/E_z2
					+ nui*p(0)/24 - E_z1*nui*p(0)/4/E_z2 - h*h*nui*p(0) + E_z1*h*h*nui*p(0) + p(0)*p(0)*p(0)/3
					+ nui*p(0)*p(0)*p(0)/6;
			U_z2_slagaemoe = -E_z1*h/2/E_z2 - 4.0*h*h*h/3 + 2.0*E_z1*h*h*h/E_z2 + h*nui/12 - E_z1*h*nui/2/E_z2
					- 5.0*h*h*h*nui/3 + 2.0*E_z1*h*h*h*nui/E_z2;
			U_z3 = E_z1*h/4/E_z3 + 2.0*h*h*h/3 - E_z1*h*h*h/E_z3 - h*nui/24 - E_z1*h*nui/4/E_z3
					+ 5.0*h*h*h*nui/6 - E_z1*h*h*h*nui/E_z2 - E_z1*p(0)/4/E_z3 - h*h*p(0) + E_z1*h*h*p(0)/E_z3
					+ nui*p(0)/24 - E_z1*nui*p(0)/4/E_z3 - h*h*nui*p(0) + E_z1*h*h*nui*p(0)/E_z3
					+ p(0)*p(0)*p(0)/3 + p(0)*p(0)*p(0)*nui/6;
			if(p(0)<=-h) {return U_z1_original + C_1;}
			else if(p(0)<h) {return U_z1_slagaemoe + U_z2_original + C_1;}
			else {return U_z1_slagaemoe + U_z2_slagaemoe + U_z3 + C_1;}
       break;
   case 3:
			U_z1_original = -1.0/12 - nui/12 - p(0)/4 - 5.0*nui*p(0)/24 + p(0)*p(0)*p(0)/3 + nui*p(0)*p(0)*p(0)/6;
			U_z1_slagaemoe = -1.0/12 - h/4 + h*h*h/3 - nui/12 - 5.0*h*nui/24 + nui*h*h*h/6;
			U_z2_original = -E_z1*h/4/E_z2 - 2.0*h*h*h/3 + E_z1*h*h*h/E_z2 + h*nui/24 - E_z1*h*nui/4/E_z2
					- 5.0*h*h*h*nui/6 + E_z1*h*h*h*nui/E_z2 - E_z1*p(0)/4/E_z2 - h*h*p(0) + E_z1*h*h*p(0)/E_z2
					+ nui*p(0)/24 - E_z1*nui*p(0)/4/E_z2 - h*h*nui*p(0) + E_z1*h*h*nui*p(0) + p(0)*p(0)*p(0)/3
					+ nui*p(0)*p(0)*p(0)/6;
			U_z2_slagaemoe = -E_z1*h/2/E_z2 - 4.0*h*h*h/3 + 2.0*E_z1*h*h*h/E_z2 + h*nui/12 - E_z1*h*nui/2/E_z2
					- 5.0*h*h*h*nui/3 + 2.0*E_z1*h*h*h*nui/E_z2;
			U_z3 = E_z1*h/4/E_z3 + 2.0*h*h*h/3 - E_z1*h*h*h/E_z3 - h*nui/24 - E_z1*h*nui/4/E_z3
					+ 5.0*h*h*h*nui/6 - E_z1*h*h*h*nui/E_z2 - E_z1*p(0)/4/E_z3 - h*h*p(0) + E_z1*h*h*p(0)/E_z3
					+ nui*p(0)/24 - E_z1*nui*p(0)/4/E_z3 - h*h*nui*p(0) + E_z1*h*h*nui*p(0)/E_z3
					+ p(0)*p(0)*p(0)/3 + p(0)*p(0)*p(0)*nui/6;
			if(p(0)<=-h) {return U_z1_original + C_1;}
			else if(p(0)<h) {return U_z1_slagaemoe + U_z2_original + C_1;}
			else {return U_z1_slagaemoe + U_z2_slagaemoe + U_z3 + C_1;}
       break;
   case 4:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  ch_ = (2*j-1) * Pi * p(1);
			  ch = 0.5 * ( exp(ch_) + exp(-ch_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( ch / sh ) + 8.0 * drob / ( Pi*(2*j-1) )   ) * cos((2*j-1)*Pi*(p(0)+0.5));
		}
//       return Summ;
	   //return Summ - nui * (  ( -p(1)*p(1)/2+C0 )*(p(0)-c0) + (p(0)-c0)*(p(0)-c0)*(p(0)-c0)/6  );
	   return 0;
       break;
   case 5:
       b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  ch_ = (2*j-1) * Pi * p(1);
			  ch = 0.5 * ( exp(ch_) + exp(-ch_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi; 
			  Summ += (   nui * b * 4.0 * drob * ( ch / sh ) + 8.0 * drob / ( Pi*(2*j-1) )   ) * cos((2*j-1)*Pi*p(0));
		}
       return Summ;
	   break;
   case 6:
       b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  ch_ = (2*j-1) * Pi * p(1);
			  ch = 0.5 * ( exp(ch_) + exp(-ch_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( ch / sh ) + 8.0 * drob / ( Pi*(2*j-1) )   ) * cos((2*j-1)*Pi*p(0));
		}
       return Summ;
	   break;}
}
template <int dim>
double FunctionAnalisys<dim>::mygradientX (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{
	double h=0.5/3;
	double U_z1_original, U_z1_slagaemoe, U_z2_original, U_z2_slagaemoe, U_z3;
	double ch, ch_, sh, sh_, Summ;
	double b = 1.0, drob = 0.0;
	double C0 = 0.0, c0 = 0.0;
	
  switch( NumberOfProblem ) {
   case 1:
			U_z1_original = -0.25 - 5.0*nui/24 + p(0)*p(0) + nui*p(0)*p(0)/2;
			U_z1_slagaemoe = 0;
			U_z2_original = - E_z1/4/E_z2 - h*h + E_z1*h*h/E_z2
					+ nui/24 - E_z1*nui/4/E_z2 - h*h*nui + E_z1*h*h*nui + p(0)*p(0)
					+ nui*p(0)*p(0)/2;
			U_z2_slagaemoe = 0;
			U_z3 =  - E_z1/4/E_z3 - h*h + E_z1*h*h/E_z3
					+ nui/24 - E_z1*nui/4/E_z3 - h*h*nui + E_z1*h*h*nui/E_z3
					+ p(0)*p(0) + p(0)*p(0)*nui/2;
			if(p(0)<=-h) {return U_z1_original;}
			else if(p(0)<h) {return U_z1_slagaemoe + U_z2_original;}
			else {return U_z1_slagaemoe + U_z2_slagaemoe + U_z3;}
       break;
   case 2:
			U_z1_original = -0.25 - 5.0*nui/24 + p(0)*p(0) + nui*p(0)*p(0)/2;
			U_z1_slagaemoe = 0;
			U_z2_original = - E_z1/4/E_z2 - h*h + E_z1*h*h/E_z2
					+ nui/24 - E_z1*nui/4/E_z2 - h*h*nui + E_z1*h*h*nui + p(0)*p(0)
					+ nui*p(0)*p(0)/2;
			U_z2_slagaemoe = 0;
			U_z3 =  - E_z1/4/E_z3 - h*h + E_z1*h*h/E_z3
					+ nui/24 - E_z1*nui/4/E_z3 - h*h*nui + E_z1*h*h*nui/E_z3
					+ p(0)*p(0) + p(0)*p(0)*nui/2;
			if(p(0)<=-h) {return U_z1_original;}
			else if(p(0)<h) {return U_z1_slagaemoe + U_z2_original;}
			else {return U_z1_slagaemoe + U_z2_slagaemoe + U_z3;}
       break;
   case 3:
			U_z1_original = -0.25 - 5.0*nui/24 + p(0)*p(0) + nui*p(0)*p(0)/2;
			U_z1_slagaemoe = 0;
			U_z2_original = - E_z1/4/E_z2 - h*h + E_z1*h*h/E_z2
					+ nui/24 - E_z1*nui/4/E_z2 - h*h*nui + E_z1*h*h*nui + p(0)*p(0)
					+ nui*p(0)*p(0)/2;
			U_z2_slagaemoe = 0;
			U_z3 =  - E_z1/4/E_z3 - h*h + E_z1*h*h/E_z3
					+ nui/24 - E_z1*nui/4/E_z3 - h*h*nui + E_z1*h*h*nui/E_z3
					+ p(0)*p(0) + p(0)*p(0)*nui/2;
			if(p(0)<=-h) {return U_z1_original;}
			else if(p(0)<h) {return U_z1_slagaemoe + U_z2_original;}
			else {return U_z1_slagaemoe + U_z2_slagaemoe + U_z3;}
       break;
   case 4:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  ch_ = (2*j-1) * Pi * p(1);
			  ch = 0.5 * ( exp(ch_) + exp(-ch_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( ch / sh ) + 8.0 * drob / Pi / (2*j-1)   ) * sin((2*j-1)*Pi*(p(0)+0.5)) * (2*j-1) * Pi * (-1);
		}
	   return Summ - nui * (  ( -p(1)*p(1)/2+C0 ) + (p(0)-c0)*(p(0)-c0)/2  );
       break;
   case 5:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  ch_ = (2*j-1) * Pi * p(1);
			  ch = 0.5 * ( exp(ch_) + exp(-ch_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( ch / sh ) + 8.0 * drob / ( Pi*(2*j-1) )   ) * sin((2*j-1)*Pi*p(0)) * (2*j-1) * Pi * (-1);
		}
       return Summ;
       break;
   case 6:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  ch_ = (2*j-1) * Pi * p(1);
			  ch = 0.5 * ( exp(ch_) + exp(-ch_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( ch / sh ) + 8.0 * drob / ( Pi*(2*j-1) )   ) * sin((2*j-1)*Pi*p(0)) * (2*j-1) * Pi * (-1);
		}
       return Summ;
       break;}
}
template <int dim>
double FunctionAnalisys<dim>::mygradientY (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{
	double sh_zn, sh_zn_, sh, sh_, Summ;
	double b = 1.0, drob = 0.0;
	double C0 = 0.0, c0 = 0.0;
	
  switch( NumberOfProblem ) {
   case 1:
	   return 0;
       break;
   case 2:
	   return 0;
       break;
   case 3:
	   return 0;
       break;
   case 4:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  sh_zn_ = (2*j-1) * Pi * p(1);
			  sh_zn = 0.5 * ( exp(sh_zn_) - exp(-sh_zn_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( sh_zn * (2*j-1) * Pi / sh )   ) * cos((2*j-1)*Pi*(p(0)+0.5));
		}
	   return Summ - nui * (  -p(1)*(p(0)-c0)  );
       break;
   case 5:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  sh_zn_ = (2*j-1) * Pi * p(1);
			  sh_zn = 0.5 * ( exp(sh_zn_) - exp(-sh_zn_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( sh_zn * (2*j-1) * Pi / sh )   ) * cos((2*j-1)*Pi*p(0));
		}
       return Summ;
       break;
   case 6:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
			  sh_zn_ = (2*j-1) * Pi * p(1);
			  sh_zn = 0.5 * ( exp(sh_zn_) - exp(-sh_zn_) );
			  sh_ = (2*j-1) * Pi * 0.5 * b;
			  sh = 0.5 * ( exp(sh_) - exp(-sh_) );
			  drob = 1.0 / (2*j-1) / (2*j-1) / (2*j-1) / Pi / Pi / Pi;
			  Summ += (   nui * b * 4.0 * drob * ( sh_zn * (2*j-1) * Pi / sh )   ) * cos((2*j-1)*Pi*p(0));
		}
       return Summ;
       break;}
}
//------------------------------------------------------------------------------
						                                                           //объявление объектов
const Tau_zz<2> tau_zz;
const U_x<2>     u_x;
const U_y<2>     u_y;
const FunctionAnalisys<2> functionAnalisys;

//------------------------------------------------------------------------------
template <int dim>
class Tau_zx : public Function<dim>
{
  public:
    Tau_zx () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double Tau_zx<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задание функции Tau_zx
	double b = 0.0, Summ = 0.0, ch_ = 0.0, ch = 0.0, sh_ = 0.0, sh = 0.0;
	double drob = 0.0, proizv = 0.0;
	
  switch( NumberOfProblem ) {
   case 1:
       return 0;
       break;
   case 2:
       return 0;
       break;
   case 3:
       return 0;
       break;
   case 4:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
		   proizv = (2*j-1) * Pi;
		   ch_ = proizv * p(1);
		   ch = 0.5 * ( exp(ch_) + exp(-ch_) );
		   sh_ = proizv * 0.5 * b;
		   sh = 0.5 * ( exp(sh_) - exp(-sh_) );
		   drob = 1.0 / (proizv * proizv);
		   Summ += (   nui * b * 4.0 * drob * ( ch / sh ) + 8.0 * drob / proizv   ) * sin(proizv*(p(0)+0.5));
		}
       //return -mu_zx.value(p) * Summ + 0.0 * mu_zx.value(p) * u_x.value(p);
	   return 0;	  
       break;
   case 5:
       return 0;
       break;
   case 6:
       return 0;
       break;}
}
//------------------------------------------------------------------------------
template <int dim>
class Tau_zy : public Function<dim>
{
  public:
    Tau_zy () : Function<dim>() {}

    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};
template <int dim>
double Tau_zy<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задание функции Tau_zy
	double b = 0.0, Summ = 0.0, sh_zn_ = 0.0, sh_zn = 0.0, sh_ = 0.0, sh = 0.0;
	double drob = 0.0, proizv = 0.0;
	
  switch( NumberOfProblem ) {
   case 1:
       return 0;
       break;
   case 2:
       return 0;
       break;
   case 3:
       return 0;
       break;
   case 4:
	   b = width, drob = 0.0;
	   Summ = 0.0;
	   for(int j=1; j<=4; ++j)
		{
		   proizv = (2*j-1) * Pi;
		   sh_zn_ = proizv * p(1);
		   sh_zn = 0.5 * ( exp(sh_zn_) - exp(-sh_zn_) );
		   sh_ = proizv * 0.5 * b;
		   sh = 0.5 * ( exp(sh_) - exp(-sh_) );
		   drob = 1.0 / (proizv * proizv);
		   Summ += (   nui * b * 4.0 * drob * ( sh_zn / sh )   ) * cos(proizv*(p(0)+0.5));
		}
       //return mu_zy.value(p) * Summ + 2.0 * mu_zy.value(p) * u_y.value(p);
	   return 0;
       break;
   case 5:
       return 0;
       break;
   case 6:
       return 0;
       break;}
}
//------------------------------------------------------------------------------
const Tau_zx<2> tau_zx_anal;
const Tau_zy<2> tau_zy_anal;




  template <int dim>
  class SolutionBase
  {
    protected:
      static const unsigned int n_source_centers = 3;
      static const Point<dim>   source_centers[n_source_centers];
      static const double       width;
  };
  template <int dim>
  class Solution : public Function<dim>,
                   protected SolutionBase<dim>
  {
    public:
      Solution () : Function<dim>() {}
      virtual double value (const Point<dim>   &p,
                            const unsigned int  component = 0) const;
      virtual Tensor<1,dim> gradient (const Point<dim>   &p,
                                      const unsigned int  component = 0) const;
  };
  template <int dim>
  double Solution<dim>::value (const Point<dim>   &p, const unsigned int) const
  {                                                                             //г.у. 1-го рода
      return 0;
  }
  template <int dim>
  Tensor<1,dim> Solution<dim>::gradient (const Point<dim> &p, const unsigned int) const
  {																				//г.у. 2-го рода
	  return 0;
  }

//template<uint8_t dim>
//dealii::Point<dim, double> get_grad (
//        const typename dealii::DoFHandler<dim>::active_cell_iterator &cell,
//        const dealii::Vector<double> &solution)
//{
//    dealii::Point<dim, double> grad;
//
//    double x1 = cell->vertex(0)(0);
//    double x2 = cell->vertex(1)(0);
//    double x3 = cell->vertex(2)(0);
//    double x4 = cell->vertex(3)(0);
//
//    double y1 = cell->vertex(0)(1);
//    double y2 = cell->vertex(1)(1);
//    double y3 = cell->vertex(2)(1);
//    double y4 = cell->vertex(3)(1);
//
//    double f1 = solution(cell->vertex_dof_index (0, 0));
//    double f2 = solution(cell->vertex_dof_index (1, 0));
//    double f3 = solution(cell->vertex_dof_index (2, 0));
//    double f4 = solution(cell->vertex_dof_index (3, 0));
//	
////	double y_1 = ( ( y3 - y2 ) / ( x3 - x2 ) ) * ( x1 - x2 ) + y2;			//было
////	double y_2 = ( ( y1 - y4 ) / ( x1 - x4 ) ) * ( x2 - x4 ) + y4;
////	double y_3 = ( ( y1 - y4 ) / ( x1 - x4 ) ) * ( x3 - x4 ) + y4;
////	double y_4 = ( ( y3 - y2 ) / ( x3 - x2 ) ) * ( x4 - x2 ) + y2;
//	double y_1 = y2 - ( ( y3 - y2 ) / ( x3 - x2 ) ) * ( x2 - x1 );			//новое
//	double y_2 = y3 - ( ( y4 - y3 ) / ( x4 - x3 ) ) * ( x3 - x2 );
//	double y_3 = y4 - ( ( y1 - y4 ) / ( x1 - x4 ) ) * ( x4 - x3 );
//	double y_4 = y1 - ( ( y2 - y1 ) / ( x2 - x1 ) ) * ( x1 - x4 );
//	
////	double x__1 = ( y1 - y3 ) * ( ( x4 - x3 ) / ( y4 - y3 ) ) + x3;
////	double x__2 = ( y2 - y3 ) * ( ( x4 - x3 ) / ( y4 - y3 ) ) + x3;
////	double x__3 = ( y3 - y1 ) * ( ( x2 - x1 ) / ( y2 - y1 ) ) + x1;
////	double x__4 = ( y4 - y1 ) * ( ( x2 - x1 ) / ( y2 - y1 ) ) + x1;
//	double x__1, x__2, x__3, x__4;
//	if (y2 == y3) { x__1 = x3 - ( ( x4 - x3 ) / ( y4 - y3 ) ) * ( y3 - y1 ); }	else { x__1 = x2 - ( ( x3 - x2 ) / ( y3 - y2 ) ) * ( y2 - y1 ); }
//	if (y3 == y4) { x__2 = x4 - ( ( x1 - x4 ) / ( y1 - y4 ) ) * ( y4 - y2 ); }	else { x__2 = x3 - ( ( x4 - x3 ) / ( y4 - y3 ) ) * ( y3 - y2 ); }
//	if (y4 == y1) { x__3 = x1 - ( ( x2 - x1 ) / ( y2 - y1 ) ) * ( y1 - y3 ); }	else { x__3 = x4 - ( ( x1 - x4 ) / ( y1 - y4 ) ) * ( y4 - y3 ); }
//	if (y1 == y2) { x__4 = x2 - ( ( x3 - x2 ) / ( y3 - y2 ) ) * ( y2 - y4 ); }	else { x__4 = x1 - ( ( x2 - x1 ) / ( y2 - y1 ) ) * ( y1 - y4 ); }
//					
//	
//	double f_1 = f2 - ( ( f3 - f2 ) / ( x3 - x2 ) ) * ( x2 - x1 );
//	double f_2 = f3 - ( ( f4 - f3 ) / ( x4 - x3 ) ) * ( x3 - x2 );
//	double f_3 = f4 - ( ( f1 - f4 ) / ( x1 - x4 ) ) * ( x4 - x3 );
//	double f_4 = f1 - ( ( f2 - f1 ) / ( x2 - x1 ) ) * ( x1 - x4 );
//	
//	double f__1, f__2, f__3, f__4;
//	if (y2 == y3) { f__1 = f3 - ( ( f4 - f3 ) / ( y4 - y3 ) ) * ( y3 - y1 ); }	else { f__1 = f2 - ( ( f3 - f2 ) / ( y3 - y2 ) ) * ( y2 - y1 ); }
//	if (y3 == y4) { f__2 = f4 - ( ( f1 - f4 ) / ( y1 - y4 ) ) * ( y4 - y2 ); }	else { f__2 = f3 - ( ( f4 - f3 ) / ( y4 - y3 ) ) * ( y3 - y2 ); }
//	if (y4 == y1) { f__3 = f1 - ( ( f2 - f1 ) / ( y2 - y1 ) ) * ( y1 - y3 ); }	else { f__3 = f4 - ( ( f1 - f4 ) / ( y1 - y4 ) ) * ( y4 - y3 ); }
//	if (y1 == y2) { f__4 = f2 - ( ( f3 - f2 ) / ( y3 - y2 ) ) * ( y2 - y4 ); }	else { f__4 = f1 - ( ( f2 - f1 ) / ( y2 - y1 ) ) * ( y1 - y4 ); }
////	double f__1 = f2 - ( ( f3 - f2 ) / ( y3 - y2 ) ) * ( y2 - y1 );
////	double f__2 = f3 - ( ( f4 - f3 ) / ( y4 - y3 ) ) * ( y3 - y2 );
////	double f__3 = f4 - ( ( f1 - f4 ) / ( y1 - y4 ) ) * ( y4 - y3 );
////	double f__4 = f1 - ( ( f2 - f1 ) / ( y2 - y1 ) ) * ( y1 - y4 );
//	
////	switch(index_vertex)														
////		{
////		  case 0 : grad(0) = ( f1 - f__1 ) / ( x1 - x__1 ); break;
////		  case 1 : grad(0) = ( f2 - f__2 ) / ( x2 - x__2 ); break;
////		  case 2 : grad(0) = ( f3 - f__3 ) / ( x3 - x__3 ); break;
////		  case 3 : grad(0) = ( f4 - f__4 ) / ( x4 - x__4 ); break;
////		}
////	switch(index_vertex)														
////		{
////		  case 0 : grad(1) = ( f1 - f_1 ) / ( y1 - y_1 ); break;
////		  case 1 : grad(1) = ( f2 - f_2 ) / ( y2 - y_2 ); break;
////		  case 2 : grad(1) = ( f3 - f_3 ) / ( y3 - y_3 ); break;
////		  case 3 : grad(1) = ( f4 - f_4 ) / ( y4 - y_4 ); break;
////		}
//	
//	
//	grad(0) = 0.25 * ( f1 - f__1 ) / ( x1 - x__1 );
//	grad(0) += 0.25 * ( f2 - f__2 ) / ( x2 - x__2 );
//	grad(0) += 0.25 * ( f3 - f__3 ) / ( x3 - x__3 );
//	grad(0) += 0.25 * ( f4 - f__4 ) / ( x4 - x__4 );
//	
//	grad(1) = 0.25 * ( f1 - f_1 ) / ( y1 - y_1 );
//	grad(1) += 0.25 * ( f2 - f_2 ) / ( y2 - y_2 );
//	grad(1) += 0.25 * ( f3 - f_3 ) / ( y3 - y_3 );
//	grad(1) += 0.25 * ( f4 - f_4 ) / ( y4 - y_4 );
//		
//	return grad;
//}

//uint8_t Function1 (
//		const typename dealii::DoFHandler<2>::active_cell_iterator &cell,
//        FILE *Ftau,
//		double mashtab,
//		const dealii::Vector<double> &solution)
//{
//	double tau_zx=0.0, tau_zy=0.0, tau_zx_Analytical=0.0, tau_zy_Analytical=0.0;
//	double Delt_abs_X = 0.0, Delt_abs_Y = 0.0, Delt_otn_X = 0.0, Delt_otn_Y = 0.0;
//	double grX=0.0, grY=0.0;
//	Point<2> middle_of_cell(0.0,0.0);
//	
//					middle_of_cell[0] = 0.25 * (cell->vertex(0)[0] + cell->vertex(1)[0] + cell->vertex(2)[0] + cell->vertex(3)[0]);
//					middle_of_cell[1] = 0.25 * (cell->vertex(0)[1] + cell->vertex(1)[1] + cell->vertex(2)[1] + cell->vertex(3)[1]);
//					
//					grX = get_grad<2> (cell, solution)[0];
//					grY = get_grad<2> (cell, solution)[1];
//					
//					tau_zx = mu_zx.value(middle_of_cell)*(u_x.value(middle_of_cell) + grX);
//					tau_zy = mu_zy.value(middle_of_cell)*(u_y.value(middle_of_cell) + grY);
//
////					grX = functionAnalisys.mygradientX(cell->vertex(i));
////					grY = functionAnalisys.mygradientY(cell->vertex(i));
////					tau_zx_Analytical = mu_zx.value(cell->vertex(i))*(u_x.value(cell->vertex(i)) + grX);
////					tau_zy_Analytical = mu_zy.value(cell->vertex(i))*(u_y.value(cell->vertex(i)) + grY);
//					tau_zx_Analytical = tau_zx_anal.value(middle_of_cell);
//					tau_zy_Analytical = tau_zy_anal.value(middle_of_cell);
//					
//					
//					Delt_abs_X = std::abs(tau_zx-tau_zx_Analytical);
//					Delt_abs_Y = std::abs(tau_zy-tau_zy_Analytical);
//
//					Delt_otn_X = std::abs(Delt_abs_X/tau_zx_Analytical)*100;
//					Delt_otn_Y = std::abs(Delt_abs_Y/tau_zy_Analytical)*100;
//					
//					//		x						y					tau_zx					tau_zy					tau_zx(An)				tau_zy(An)				Delt(tau_zx)			Delt(tau_zy)			%(tau_zx)						%(tau_zy)
//					fprintf(Ftau,"%16.8f\t\t%16.8f\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\r\n", 
////							middle_of_cell[0], middle_of_cell[1], mashtab*tau_zx, mashtab*tau_zy, mashtab*tau_zx_Analytical, 
//							cell->vertex(0)[0], cell->vertex(0)[1], mashtab*tau_zx, mashtab*tau_zy, mashtab*tau_zx_Analytical, 
//							mashtab*tau_zy_Analytical, Delt_abs_X, Delt_abs_Y, Delt_otn_X, Delt_otn_Y);
//					
//    return 1;
//}


template <int dim>
class Step6
{
  public:
    Step6 ();
    ~Step6 ();

	void calculate_grad_on_cells ();
	void result_U_z ();
    void run ();

  private:
    void setup_system ();
    void assemble_system ();
    void solve ();
    void refine_grid ();
    void output_results () const;
    Triangulation<dim>   triangulation;
    DoFHandler<dim>      dof_handler;
    FE_Q<dim>            fe;
    ConstraintMatrix     hanging_node_constraints;
    SparsityPattern      sparsity_pattern;
    SparseMatrix<double> system_matrix;
    Vector<double>       solution;
    Vector<double>       system_rhs;
};

template <int dim>
class BoundaryValues : public Function<dim>
{
  public:
    BoundaryValues () : Function<dim>() {}
    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};

template <int dim>
class RightHandSide : public Function<dim>
{
  public:
    RightHandSide () : Function<dim>() {}
    virtual double value (const Point<dim>   &p,
                          const unsigned int  component = 0) const;
};

template <int dim>
double BoundaryValues<dim>::value (const Point<dim> &p,
                                   const unsigned int /*component*/) const
{
	return 0;                                                          //!!!!задаётся аналитическая функция для границы
}

template <int dim>
double RightHandSide<dim>::value (const Point<dim> &p,
                                  const unsigned int /*component*/) const
{                                                                               //задаётся источник с минусом
	return 0;
}

template <int dim>
Step6<dim>::Step6 ()
                :
                dof_handler (triangulation),
                fe (1)
{}

template <int dim>
Step6<dim>::~Step6 ()
{
  dof_handler.clear ();
}

template <int dim>
void Step6<dim>::setup_system ()
{
  dof_handler.distribute_dofs (fe);
  solution.reinit (dof_handler.n_dofs());
  system_rhs.reinit (dof_handler.n_dofs());
  hanging_node_constraints.clear ();
  DoFTools::make_hanging_node_constraints (dof_handler,
                                           hanging_node_constraints);
  hanging_node_constraints.close ();
  CompressedSparsityPattern c_sparsity(dof_handler.n_dofs());
  DoFTools::make_sparsity_pattern (dof_handler, c_sparsity);
  hanging_node_constraints.condense (c_sparsity);
  sparsity_pattern.copy_from(c_sparsity);
  system_matrix.reinit (sparsity_pattern);
}

template <int dim>
void Step6<dim>::assemble_system ()
{
  const QGauss<dim>  quadrature_formula(3);
  QGauss<dim-1> face_quadrature_formula(3);
  const RightHandSide<dim> right_hand_side;
  const unsigned int n_face_q_points = face_quadrature_formula.size();
  FEValues<dim> fe_values (fe, quadrature_formula,
                           update_values    |  update_gradients |
                           update_quadrature_points  |  update_JxW_values);
  FEFaceValues<dim> fe_face_values (fe, face_quadrature_formula,
                                      update_values         | update_quadrature_points  |
                                      update_normal_vectors | update_JxW_values);
  const unsigned int   dofs_per_cell = fe.dofs_per_cell;
  const unsigned int   n_q_points    = quadrature_formula.size();
  FullMatrix<double>   cell_matrix (dofs_per_cell, dofs_per_cell);
  Vector<double>       cell_rhs (dofs_per_cell);
  std::vector<unsigned int> local_dof_indices (dofs_per_cell);

												
  typename DoFHandler<dim>::active_cell_iterator
    cell = dof_handler.begin_active(),
    endc = dof_handler.end();
  for (; cell!=endc; ++cell)
    {
      cell_matrix = 0;
	  
      cell_rhs = 0;
      fe_values.reinit (cell);
      for (unsigned int q_point=0; q_point<n_q_points; ++q_point)
        for (unsigned int i=0; i<dofs_per_cell; ++i)
          {
            for (unsigned int j=0; j<dofs_per_cell; ++j)

            cell_matrix(i,j) += (mu_zx.value (fe_values.quadrature_point (q_point)) *
                                 fe_values.shape_grad(i,q_point)[0] *
                                 fe_values.shape_grad(j,q_point)[0] *
                                 fe_values.JxW(q_point)

                                 + mu_zy.value (fe_values.quadrature_point (q_point)) *
                                 fe_values.shape_grad(i,q_point)[1] *
                                 fe_values.shape_grad(j,q_point)[1] *
                                 fe_values.JxW(q_point)
                    );

			cell_rhs(i) += (tau_zz.value(fe_values.quadrature_point (q_point)) *
							fe_values.shape_value(i,q_point) *
							fe_values.JxW(q_point) -

							mu_zx.value (fe_values.quadrature_point (q_point)) *
							fe_values.shape_grad(i,q_point)[0] *
							u_x.value(fe_values.quadrature_point (q_point)) *
							fe_values.JxW(q_point) -

							mu_zy.value (fe_values.quadrature_point (q_point)) *
							fe_values.shape_grad(i,q_point)[1] *
							u_y.value(fe_values.quadrature_point (q_point)) *
							fe_values.JxW(q_point)
							);

          }
	  
//------------------------------------------------------------------------------

      cell->get_dof_indices (local_dof_indices);
      for (unsigned int i=0; i<dofs_per_cell; ++i)
        {
          for (unsigned int j=0; j<dofs_per_cell; ++j)
            system_matrix.add (local_dof_indices[i],
                               local_dof_indices[j],
                               cell_matrix(i,j));

          system_rhs(local_dof_indices[i]) += cell_rhs(i);
        }

    }
  
  hanging_node_constraints.condense (system_matrix);
  hanging_node_constraints.condense (system_rhs);
  std::map<unsigned int,double> boundary_values;
  MatrixTools::apply_boundary_values (boundary_values,
                                      system_matrix,
                                      solution,
                                      system_rhs);
}


template <int dim>
void Step6<dim>::solve ()
{
  SolverControl           solver_control (1000, 1e-12);
  SolverCG<>              solver (solver_control);
  PreconditionSSOR<> preconditioner;
  preconditioner.initialize(system_matrix, 1.2);
  solver.solve (system_matrix, solution, system_rhs,
                preconditioner);
  hanging_node_constraints.distribute (solution);
}


template <int dim>
void Step6<dim>::refine_grid ()
{
  Vector<float> estimated_error_per_cell (triangulation.n_active_cells());
  KellyErrorEstimator<dim>::estimate (dof_handler,
                                      QGauss<dim-1>(3),
                                      typename FunctionMap<dim>::type(),
                                      solution,
                                      estimated_error_per_cell);
  GridRefinement::refine_and_coarsen_fixed_number (triangulation,
                                                   estimated_error_per_cell,
                                                   0.3, 0.03);
  triangulation.execute_coarsening_and_refinement ();
}


template <int dim>
void Step6<dim>::output_results () const
{
  std::string filename = "triangulation";
  std::ofstream output (filename.c_str());
  GridOut grid_out;
  grid_out.write_eps (triangulation, output);
}

template<int dim>
void Step6<dim>::result_U_z ()
{
	FILE *Ftau;
	Point<2> middle_of_cell(0.0,0.0);
    Ftau = fopen ("FU_z.gpl","w");
	
	double U_z_Analytic = 0.0, U_z_Solution = 0.0;
	double Delt_abs = 0.0, Delt_otn = 0.0;
	double f1 = 0.0;
	double f2 = 0.0;
	double f3 = 0.0;
	double f4 = 0.0;
	
dealii::QGauss<dim> quadrature_formula(2);
dealii::FEValues<dim> fe_values (fe, quadrature_formula,
		dealii::update_gradients | 
		dealii::update_quadrature_points | dealii::update_JxW_values);
	  
	for (typename dealii::DoFHandler<2>::active_cell_iterator cell = dof_handler.begin_active (); cell != dof_handler.end (); ++cell)
		 {
		    f1 = solution(cell->vertex_dof_index (0, 0));
		    f2 = solution(cell->vertex_dof_index (1, 0));
		    f3 = solution(cell->vertex_dof_index (2, 0));
		    f4 = solution(cell->vertex_dof_index (3, 0));
			middle_of_cell[0] = 0.25 * (cell->vertex(0)[0] + cell->vertex(1)[0] + cell->vertex(2)[0] + cell->vertex(3)[0]);
			middle_of_cell[1] = 0.25 * (cell->vertex(0)[1] + cell->vertex(1)[1] + cell->vertex(2)[1] + cell->vertex(3)[1]);
			
			U_z_Solution = 0.25*(f1+f2+f3+f4);
			U_z_Analytic = functionAnalisys.value(middle_of_cell);
			Delt_abs = std::abs(U_z_Solution-U_z_Analytic);
			Delt_otn = std::abs(Delt_abs/U_z_Analytic)*100;
					
			fprintf(Ftau,"%16.8f\t\t%16.8f\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\r\n", 
							middle_of_cell[0], middle_of_cell[1], U_z_Solution, U_z_Analytic, Delt_abs, Delt_otn );
			
			
         }
	
	fclose(Ftau);
}

template<int dim>
void Step6<dim>::calculate_grad_on_cells ()
{
    dealii::QGauss<dim> quadrature_formula(2);
    dealii::FEValues<dim> fe_values (fe, quadrature_formula,
            dealii::update_gradients | 
            dealii::update_quadrature_points | dealii::update_JxW_values);
    const uint8_t num_quad_points = quadrature_formula.size();
	
	double tau_zx=0.0, tau_zy=0.0, tau_zx_Analytical=0.0, tau_zy_Analytical=0.0;
	double Delt_abs_X = 0.0, Delt_abs_Y = 0.0;
	double Delt_otn_X = 0.0, Delt_otn_Y = 0.0;
	FILE *Ftau;
	Ftau = fopen ("Ftau.gpl","w");
	
	double deform = 0.0, deform0 = 0.0, deform1 = 0.0;
	for (typename dealii::DoFHandler<dim>::active_cell_iterator cell = dof_handler.begin_active (); cell != dof_handler.end (); ++cell)
	{
			fe_values .reinit (cell);

			double area = 0.0;
			for(int i = 0; i < num_quad_points; ++i)
				area += fe_values.JxW(i);
		
			Point<2> middle_of_cell(0.0,0.0);
			
			for (int i : {0, 1})	//x,y
			{
				deform = 0.0;
				for(auto n : {0, 1, 2, 3})
				{
					double summ = 0.0;
					for (size_t q_point = 0; q_point < num_quad_points; ++q_point)
						summ += 
							fe_values.shape_grad (n, q_point)[i] *
							fe_values.JxW(q_point);
						deform += 
							solution(cell->vertex_dof_index(n, 0)) * 
							summ;
				};
				if(i == 0) deform0 = deform / area;
					else deform1 = deform / area;
			};

			middle_of_cell[0] = 0.25 * (cell->vertex(0)[0] + cell->vertex(1)[0] + cell->vertex(2)[0] + cell->vertex(3)[0]);
			middle_of_cell[1] = 0.25 * (cell->vertex(0)[1] + cell->vertex(1)[1] + cell->vertex(2)[1] + cell->vertex(3)[1]);
			
			tau_zx = mu_zx.value(middle_of_cell)*(u_x.value(middle_of_cell) + deform0);
			tau_zy = mu_zy.value(middle_of_cell)*(u_y.value(middle_of_cell) + deform1);
			
			tau_zx_Analytical = tau_zx_anal.value(middle_of_cell);
			tau_zy_Analytical = tau_zy_anal.value(middle_of_cell);
			
			Delt_abs_X = std::abs(tau_zx-tau_zx_Analytical);
			Delt_abs_Y = std::abs(tau_zy-tau_zy_Analytical);
			
			Delt_otn_X = std::abs(Delt_abs_X/tau_zx_Analytical)*100;
			Delt_otn_Y = std::abs(Delt_abs_Y/tau_zy_Analytical)*100;
			//		x						y					tau_zx					tau_zy					tau_zx(An)				tau_zy(An)				Delt(tau_zx)			Delt(tau_zy)			%(tau_zx)						%(tau_zy)
			fprintf(Ftau,"%16.8f\t\t%16.8f\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\t\t%16.8e\r\n", 
					middle_of_cell[0], middle_of_cell[1], tau_zx, tau_zy, tau_zx_Analytical, tau_zy_Analytical, Delt_abs_X, Delt_abs_Y, Delt_otn_X, Delt_otn_Y);
	}
	fclose(Ftau);	
};


template <int dim>
void Step6<dim>::run ()
{
//	double H = 0.0;
//	double point_p1_x=0.0, point_p1_y=0.0, point_p2_x=0.0, point_p2_y=0.0;
////	const Point<2> p1(-0.5, -0.5), p2(0.5, 0.5);
//			point_p1_x=-0.5;
//			point_p1_y=-0.5;
//			point_p2_x=0.5;
//			point_p2_y=0.5;
//	const Point<2> p1(point_p1_x, point_p1_y), p2(point_p2_x, point_p2_y);
//	
//	FILE *FInformation;
//	FInformation = fopen ("FInformation.txt","w");
//		std::cout << "\tНомер задачи: " << NumberOfProblem << std::endl;
//		fprintf(FInformation,"\tНомер задачи: %d\n",NumberOfProblem);
//		std::cout << "\tкоординаты области: " << std::endl;
//		fprintf(FInformation,"\tкоординаты области: \n");
//		std::cout << "\t(" << p1[0] << ":" << p1[1] << ")" << "\t--------------------------------\t    (" << p1[0] << ":" << p2[1] << ")" << std::endl;
//		fprintf(FInformation,"\t(%8.4f:%8.4f)\t--------------------------------\t    (%8.4f:%8.4f)\n", p1[0], p1[1], p1[0], p2[1]);
//		std::cout << "\t   |" << "\t\t|\t\t\t\t" << "|\t\t|" << std::endl;
//		fprintf(FInformation,"\t\t   |\t\t\t\t|\t\t\t\t\t\t\t\t|\t\t\t|\n");
//		std::cout << "\t   |" << "\t\t|\t\t\t\t" << "|\t\t|" << std::endl;
//		fprintf(FInformation,"\t\t   |\t\t\t\t|\t\t\t\t\t\t\t\t|\t\t\t|\n");
//		std::cout << "\t   |" << "\t\t|\t\t\t\t" << "|\t\t|" << std::endl;
//		fprintf(FInformation,"\t\t   |\t\t\t\t|\t\t\t\t\t\t\t\t|\t\t\t|\n");
//		std::cout << "\t(" << p2[0] << ":" << p1[1] << ")" << "\t--------------------------------\t    (" << p2[0] << ":" << p2[1] << ")" << std::endl << std::endl;
//		fprintf(FInformation,"\t(%8.4f:%8.4f)\t--------------------------------\t    (%8.4f:%8.4f)\n",p2[0],p1[1],p2[0],p2[1]);
//		
//		
//			   GridGenerator::hyper_rectangle(triangulation, p1, p2);						//задание прямоугольника
////		
//				
//				
//      triangulation.refine_global (N);                                          //меняется рефайн
//      std::cout << "\tNumber of active cells:       "
//                << triangulation.n_active_cells()
//                << std::endl;
//	  fprintf(FInformation,"\tNumber of active cells:       %d\n",triangulation.n_active_cells());
//      setup_system ();
//      std::cout << "\tNumber of degrees of freedom: "
//                << dof_handler.n_dofs()
//                << std::endl;
//	  fprintf(FInformation,"\tNumber of degrees of freedom: %d\n",dof_handler.n_dofs());
//	  std::cout << "\tКоличество рефайнов: "
//                << N
//                << std::endl;
//	  fprintf(FInformation,"\tКоличество рефайнов: %d\n",N);
//	  int CountOfCells=1;
//	  for(int i=0;i<N;++i) {CountOfCells *= 2;}
//	  std::cout << "\tколичество ячеек по высоте балки (вдоль X): "
//				<< CountOfCells
//                << std::endl;
//	  fprintf(FInformation,"\tколичество ячеек по ширине балки (вдоль X): %d\n",CountOfCells);
	  
	  
	  
//	  fclose(FInformation);
//==============================================================================
	
	FILE *FInformation;
	FInformation = fopen ("FInformation.txt","w");
		std::cout << "\tНомер задачи: " << NumberOfProblem << std::endl;
		fprintf(FInformation,"\tНомер задачи: %d\n",NumberOfProblem);
	  
  GridIn<dim> gridin;
  gridin.attach_triangulation(triangulation);
//  std::ifstream f("www.msh");
  std::ifstream f("untitled.msh");
  Assert (dim==2, ExcInternalError());
  gridin.read_msh(f);
  
  
  triangulation.refine_global (1); 
  const std::string filenameOut = "grid-1.eps";
  std::ofstream out (filenameOut.c_str());
  GridOut grid_out;
  grid_out.write_eps (triangulation, out);
      std::cout << "   Number of active cells: "
                << triangulation.n_active_cells()
                << std::endl
                << "   Total number of cells: "
                << triangulation.n_cells()
                << std::endl;
	  
	  fprintf(FInformation,"   Number of active cells: %d \n",triangulation.n_active_cells());
	  fprintf(FInformation,"    Total number of cells: %d \n",triangulation.n_cells());
  fclose(FInformation);

//==============================================================================
	  
	  setup_system ();
      assemble_system ();
      solve ();
      output_results();
	  
//==============================================================================
//------------------------------------------------------------------------------

  DataOutBase::EpsFlags eps_flags;
  eps_flags.z_scaling = 4;
  DataOut<dim> data_out_eps;
  data_out_eps.set_flags (eps_flags);
  data_out_eps.attach_dof_handler (dof_handler);
  data_out_eps.add_data_vector (solution, "solution");
  data_out_eps.build_patches ();
  std::ofstream output_eps ("U_z.eps");
  data_out_eps.write_eps (output_eps);
  
//------------------------------------------------------------------------------
  
  const QGauss<dim>  quadrature_formula(3);
  QGauss<dim-1> face_quadrature_formula(3);
  const RightHandSide<dim> right_hand_side;
  const unsigned int n_face_q_points = face_quadrature_formula.size();
  FEValues<dim> fe_values (fe, quadrature_formula,
                           update_values    |  update_gradients |
                           update_quadrature_points  |  update_JxW_values);
  FEFaceValues<dim> fe_face_values (fe, face_quadrature_formula,
                                      update_values         | update_quadrature_points  |
                                      update_normal_vectors | update_JxW_values);
  const unsigned int   dofs_per_cell = fe.dofs_per_cell;
  const unsigned int   n_q_points    = quadrature_formula.size();
  FullMatrix<double>   cell_matrix (dofs_per_cell, dofs_per_cell);
  Vector<double>       cell_rhs (dofs_per_cell);
  std::vector<unsigned int> local_dof_indices (dofs_per_cell);
  double FS;
  typename DoFHandler<dim>::active_cell_iterator
    cell = dof_handler.begin_active(),
    endc = dof_handler.end();
  
  integral=0.0; FS=0.0;
  for (; cell!=endc; ++cell)
    {
      fe_values.reinit (cell);
      for (unsigned int q_point=0; q_point<n_q_points; ++q_point)
          {
			FS = functionAnalisys.value (fe_values.quadrature_point (q_point));
			integral +=	FS*fe_values.JxW(q_point);
		  }
	}

//------------------------------------------------------------------------------
//==============================================================================
//------------------------------------------------------------------------------
 
	FInformation = fopen ("FInformation.txt","a");
		
	std::cout << "\n E_z1 = " << E_z1 << "\n";
	fprintf(FInformation,"\n E_z1 = %16.8f\n", E_z1);
	std::cout << "\n E_z2 = " << E_z2 << "\n";
	fprintf(FInformation,"\n E_z2 = %16.8f\n", E_z2);
	std::cout << "\n E_z3 = " << E_z3 << "\n";
	fprintf(FInformation,"\n E_z3 = %16.8f\n", E_z3);
	std::cout << "\n nui = " << nui << "\n";
	fprintf(FInformation,"\n nui = %16.8f\n", nui);
	
	fclose(FInformation);
}



int main ()
{
  try
    {
      deallog.depth_console (0);
	  
      Step6<2> laplace_problem_2d;
      laplace_problem_2d.run ();
	  laplace_problem_2d.calculate_grad_on_cells ();
	  laplace_problem_2d.result_U_z();
    }
  catch (std::exception &exc)
    {
      std::cerr << std::endl << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Exception on processing: " << std::endl
                << exc.what() << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    }

  catch (...)
    {
      std::cerr << std::endl << std::endl
                << "----------------------------------------------------"
                << std::endl;
      std::cerr << "Unknown exception!" << std::endl
                << "Aborting!" << std::endl
                << "----------------------------------------------------"
                << std::endl;
      return 1;
    }
  
  return 0;
}









  