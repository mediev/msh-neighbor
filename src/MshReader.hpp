#ifndef MSHREADER_HPP_
#define MSHREADER_HPP_

#include <string>
#include <fstream>
#include <cstdlib>

#include "Mesh.hpp"

namespace mshreader
{
	class MshReader
	{
	private:
		std::string buf;
		std::string x, y, z;
		std::string::size_type sz;
		std::vector<elem::Element> border_elems;
		std::vector<elem::Element> frac_elems;
		int vertInds[elem::MAX_ELEM_NEBR_SIZE];

		const std::string NODES_BEGIN = "$Nodes";
		const std::string NODES_END = "$EndNodes";
		const std::string ELEMS_BEGIN = "$Elements";
		const std::string ELEMS_END = "$EndElements";
		const std::string TRI_TYPE = "2";
		const std::string QUAD_TYPE = "3";
		const std::string HEX_TYPE = "5";
		const std::string PRISM_TYPE = "6";

		const std::string FRAC_REGION = "6";
		const std::string BOUND_REGION = "7";
		const std::string BORDER_HEX = "11";
	protected:
	public:
		MshReader();
		~MshReader();

		const grid::Mesh* read(const std::string filename);
		void write(const grid::Mesh* mesh, const std::string filename);
	};
};

#endif /* MSHREADER_HPP_ */