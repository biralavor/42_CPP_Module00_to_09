/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: umeneses <umeneses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:28:48 by umeneses          #+#    #+#             */
/*   Updated: 2026/01/19 22:42:12 by umeneses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

int main() {
  Data *content = new Data(42, "test", 42.42f, true);

  std::cout << "Original pointer: " << content << std::endl;
  std::cout << "Original content: {" << std::endl;
  std::cout << "\t id: " << content->id << ";" << std::endl;
  std::cout << "\t name: " << content->name << ";" << std::endl;
  std::cout << "\t value: " << content->value << ";" << std::endl;
  std::cout << "\t active: " << content->active << ";" << std::endl;
  std::cout << "}" << std::endl;

  uintptr_t raw = Serializer::serialize(content);
  std::cout << "Serialized (uintptr_t): " << raw << std::endl;

  Data *deserializedData = Serializer::deserialize(raw);
  std::cout << "////////////////////////////////////////////////" << std::endl;
  std::cout << "Deserialized pointer: " << deserializedData << std::endl;
  std::cout << "Deserialized content: {" << std::endl;
  std::cout << "\t id: " << deserializedData->id << ";" << std::endl;
  std::cout << "\t name: " << deserializedData->name << ";" << std::endl;
  std::cout << "\t value: " << deserializedData->value << ";" << std::endl;
  std::cout << "\t active: " << deserializedData->active << ";" << std::endl;
  std::cout << "}" << std::endl << std::endl;

  if (content == deserializedData)
    std::cout << "SUCCESS: Pointers match." << std::endl;
  else
    std::cout << "ERROR: Pointers do not match." << std::endl;

  delete content;

  return 0;
}