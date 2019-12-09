#pragma once


#include "TemplateHeap.hpp"

template<typename T, typename Comparison = std::greater<T>>
class MaxHeap : public TemplateHeap<T, Comparison>
{};


template<typename T, typename Comparison = std::less<T>>
class MinHeap : public TemplateHeap<T, Comparison>
{};
