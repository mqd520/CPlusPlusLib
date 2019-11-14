#include "stdafx.h"
#include "VariantHelper.h"


namespace MyAdo
{
	VariantHelper::VariantHelper(_variant_t var)
		: variant(var)
	{

	}

	int VariantHelper::Type()
	{
		return variant.vt;
	}

	int VariantHelper::Int32()
	{
		if (variant.vt == VT_INT || variant.vt == VT_I4)
		{
			return variant.intVal;
		}

		return 0;
	}

	UINT VariantHelper::UInt32()
	{
		if (variant.vt == VT_UINT || variant.vt == VT_UI4)
		{
			return variant.uintVal;
		}

		return 0;
	}

	short VariantHelper::Short()
	{
		if (variant.vt == VT_I2)
		{
			return variant.iVal;
		}

		return 0;
	}

	USHORT VariantHelper::UShort()
	{
		if (variant.vt == VT_UI2)
		{
			return variant.uiVal;
		}

		return 0;
	}

	INT64 VariantHelper::Int64()
	{
		if (variant.vt == VT_I8)
		{
			return variant.llVal;
		}

		return 0;
	}

	UINT64 VariantHelper::UInt64()
	{
		if (variant.vt == VT_UI8)
		{
			return variant.ullVal;
		}

		return 0;
	}

	float VariantHelper::Float()
	{
		if (variant.vt == VT_R4)
		{
			return variant.fltVal;
		}

		return 0;
	}

	double VariantHelper::Double()
	{
		if (variant.vt == VT_R8)
		{
			return variant.dblVal;
		}

		return 0;
	}

	DECIMAL VariantHelper::Decimal()
	{
		if (variant.vt == VT_DECIMAL)
		{
			return variant.decVal;
		}

		return DECIMAL();
	}

	bool VariantHelper::Bool()
	{
		if (variant.vt == VT_BOOL)
		{
			return variant.lVal == 0 ? false : true;
		}

		return false;
	}

	double VariantHelper::Date()
	{
		if (variant.vt == VT_DATE)
		{
			return variant.date;
		}

		return 0;
	}

	string VariantHelper::String()
	{
		if (variant.vt == VT_BSTR || variant.vt == VT_LPSTR)
		{
			return (LPCSTR)(_bstr_t)variant;
		}

		return "";
	}

	wstring VariantHelper::WString()
	{
		if (variant.vt == VT_LPWSTR)
		{
			return (LPCWSTR)(_bstr_t)variant;
		}

		return L"";
	}

	bool VariantHelper::IsNull()
	{
		return variant.vt == VT_NULL;
	}

	bool VariantHelper::IsEmpty()
	{
		return variant.vt == VT_EMPTY;
	}

	bool VariantHelper::IsUnknown()
	{
		return variant.vt == VT_UNKNOWN;
	}
}