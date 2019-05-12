#ifndef IMPORTEXPORT_HPP
#define IMPORTEXPORT_HPP

#ifdef EXPORT_KINECTCOREDLL_SYMBOL
#	define KINECTCOREDLL_API __declspec(dllexport)
#else
#	define KINECTCOREDLL_API __declspec(dllimport)
#endif

#endif // IMPORTEXPORT_HPP