#ifndef MESH_HPP_
#define MESH_HPP_

#include "Point.hpp"
#include <vector>
#include <cassert>
#include <initializer_list>
#include <array>

namespace elem
{
	static const int MAX_ELEM_POINT_SIZE = 8;
	static const int MAX_ELEM_NEBR_SIZE = 6;
	static const int QUAD_VERT_SIZE = 4;
	static const int TRI_VERT_SIZE = 3;

	enum EType { BORDER_TRI, BORDER_QUAD, FRAC_QUAD, PRISM, HEX, BORDER_HEX};

	inline const int num_of_verts(const EType type)
	{
		if (type == BORDER_TRI)
			return 3;
		else if (type == BORDER_QUAD || type == FRAC_QUAD)
			return 4;
		else if (type == PRISM)
			return 6;
		else if (type == HEX || type == BORDER_HEX)
			return 8;
	}
	inline const int num_of_nebrs(const EType type)
	{
		if (type == BORDER_TRI || type == BORDER_QUAD)
			return 1;
		else if (type == FRAC_QUAD)
			return 2;
		else if (type == PRISM)
			return 5;
		else if (type == HEX || type == BORDER_HEX)
			return 6;
	}

	struct Nebr
	{
		int id;	
		double S;
		double L;
		point::Point cent;
	};

	class Element
	{
	public:
		int num;
		EType type;

		int verts_num;
		int nebrs_num;
		std::array<int, MAX_ELEM_POINT_SIZE> verts;
		std::array<Nebr, MAX_ELEM_NEBR_SIZE> nebrs;
		point::Point cent;
		//double dist [MAX_ELEM_NEBR_SIZE];
		//double square [MAX_ELEM_NEBR_SIZE];
		double V;

		Element() {};
		Element(const EType _type, const int* _verts) : type(_type), verts_num(num_of_verts(_type)), nebrs_num(num_of_nebrs(_type))
		{
			for (int i = 0; i < verts_num; i++)
				verts[i] = _verts[i];
		};
		~Element() {};
	};
};

namespace mshreader
{
	class MshReader;
};
namespace grid
{
	class Mesh
	{
		friend class mshreader::MshReader;
	protected:
		int inner_size, border_size, frac_size, pts_size;
		std::vector<point::Point> pts;
		std::vector<elem::Element> elems;

		int check_neighbors() const;
		void set_neighbors();
		void set_point_cells();
	public:
		Mesh();
		~Mesh();

		void process_geometry();
	};
}

#endif /* MESH_HPP_ */
