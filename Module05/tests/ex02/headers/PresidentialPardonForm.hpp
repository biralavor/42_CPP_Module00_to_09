/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:12:16 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 15:46:28 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"

class PresidentialPardonForm : public AForm
{
	static const int _minGradeToSign = 25;
	static const int _minGradeToExecute = 5;

private:
	void announcement(void) const;

public:
	PresidentialPardonForm(void);
	explicit PresidentialPardonForm(const std::string &target);
	~PresidentialPardonForm(void);
	PresidentialPardonForm(PresidentialPardonForm const &src);
	PresidentialPardonForm &operator=(PresidentialPardonForm const &rightSide);
    
	virtual void action(Bureaucrat const &executor) const;
};
