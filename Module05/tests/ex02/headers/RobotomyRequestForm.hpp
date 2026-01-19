/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:11:00 by umeneses          #+#    #+#             */
/*   Updated: 2025/08/31 15:46:24 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include <cstdlib>

class RobotomyRequestForm : public AForm
{
	static const int _minGradeToSign = 72;
	static const int _minGradeToExecute = 45;

private:
	void drillingNoise(void) const;
	void successAnnouncement(void) const;
	void failureAnnouncement(void) const;
	void randomOutcome(void) const;

public:
	RobotomyRequestForm(void);
	explicit RobotomyRequestForm(const std::string &target);
	~RobotomyRequestForm(void);
	RobotomyRequestForm(RobotomyRequestForm const &src);
	RobotomyRequestForm &operator=(RobotomyRequestForm const &rightSide);
	
	virtual void action(Bureaucrat const &executor) const;
};
