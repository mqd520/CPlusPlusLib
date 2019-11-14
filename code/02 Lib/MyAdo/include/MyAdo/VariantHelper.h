#pragma once

#include <string>
using namespace std;

#include "MSAdo.h"


namespace MyAdo
{
	// VariantHelper
	class VariantHelper
	{
	public:
		VariantHelper(_variant_t var);

	protected:
		_variant_t variant;

	public:
		int Type();

		int Int32();

		UINT UInt32();

		short Short();

		USHORT UShort();

		INT64 Int64();

		UINT64 UInt64();

		float Float();

		double Double();

		DECIMAL Decimal();

		bool Bool();

		double Date();

		string String();

		wstring WString();

		bool IsNull();

		bool IsEmpty();

		bool IsUnknown();
	};
}