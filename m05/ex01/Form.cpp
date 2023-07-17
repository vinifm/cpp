/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viferrei <viferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:27:55 by viferrei          #+#    #+#             */
/*   Updated: 2023/07/17 18:10:44 by viferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

/*--- CONSTRUCTORS AND DESTRUCTOR --------------------------------------------*/

Form::Form() :
	_name("Blank"), _signed(false), _signGrade(150), _execGrade(150) {
		std::cout << "You've found a blank" YELLOW " Form. " RESET
			<< "It's pretty useless."
			<< std::endl;
}

Form::Form(
	const std::string name,
	const unsigned int signGrade,
	const unsigned int execGrade
	) :
	_name(name), _signGrade(signGrade), _execGrade(execGrade) {
		checkGrade(signGrade);
		checkGrade(execGrade);
		std::cout << YELLOW "Form " RESET << "\""
			<< getName() << "\" with sign grade "
			<< getSignGrade() << " and execute grade "
			<< getExecGrade() << " is delivered to your desk."
			<< std::endl;
}

Form::Form(const Form& copy) :
	_name(copy.getName()),
	_signGrade(copy.getSignGrade()),
	_execGrade(copy.getExecGrade()) {
		*this = copy;
		std::cout << YELLOW "Form " RESET "Copy constructor called"
			<< std::endl;
}

Form&	Form::operator=(const Form &rhs) {
	std::cout << YELLOW "Form " RESET "Copy assignment operator called"
		<< std::endl;
	if (this != &rhs)
		_signed = rhs.getSigned();
	return *this;
}

Form::~Form() {
	std::cout << YELLOW "Form " RESET
		<< getName() << " has been shredded."
		<< std::endl;
}

/*--- MEMBER FUNCTIONS -------------------------------------------------------*/

/* Change form status to signed if Bureaucrat grade is high enough */
void	Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > getSignGrade())
		throw GradeTooLowException();
	_signed = true;
}

void	Form::checkGrade(const unsigned int grade) {
	if (grade < 1)
		throw GradeTooHighException();
	else if (grade > 150)
		throw GradeTooLowException();
}

/*--- ACCESSORS --------------------------------------------------------------*/

const std::string	Form::getName() const { return _name; }
bool				Form::getSigned() const { return _signed; }
unsigned int		Form::getSignGrade() const { return _signGrade; }
unsigned int		Form::getExecGrade() const { return _execGrade; }

/*--- EXCEPTIONS -------------------------------------------------------------*/

const char* Form::GradeTooHighException::what() const throw() {
	return "Grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw() {
	return "Grade is too low!";
}

/*--- INSERTION OPERATOR OVERLOAD --------------------------------------------*/

std::ostream& operator<<(std::ostream& os, const Form& form) {
	std::string signed_status = "unsigned";

	if (form.getSigned())
		signed_status = "signed";
	os << signed_status << YELLOW " Form " RESET << "\""
		<< form.getName() << "\" has sign grade "
		<< form.getSignGrade() << " and execute grade "
		<< form.getExecGrade();
	return os;
}
