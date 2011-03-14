// fstream standard header
#pragma once
#ifndef _FSTREAM_
#define _FSTREAM_
#ifndef RC_INVOKED
#include <istream>

#ifdef  _MSC_VER
#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)

 #pragma warning(disable: 4127)
#endif  /* _MSC_VER */

_STD_BEGIN

extern _MRTIMP2_NCEEPURE _Filet *__CLRCALL_PURE_OR_CDECL _Fiopen(const char *,
	ios_base::openmode, int);
extern _MRTIMP2_NCEEPURE _Filet *__CLRCALL_PURE_OR_CDECL _Fiopen(const wchar_t *,
	ios_base::openmode, int);

#ifdef _NATIVE_WCHAR_T_DEFINED
extern _MRTIMP2_NCEEPURE _Filet *__CLRCALL_PURE_OR_CDECL _Fiopen(const unsigned short *,
	ios_base::openmode, int);
 #endif /* _NATIVE_WCHAR_T_DEFINED */

		// TEMPLATE FUNCTION _Fgetc
template<class _Elem> inline
	bool _Fgetc(_Elem& _Ch, _Filet *_File)
	{	// get an element from a C stream
	return (fread(&_Ch, sizeof (_Elem), 1, _File) == 1);
	}

template<> inline bool _Fgetc(char& _Byte, _Filet *_File)
	{	// get a char element from a C stream
	int _Meta;
	if ((_Meta = fgetc(_File)) == EOF)
		return (false);
	else
		{	// got one, convert to char
		_Byte = (char)_Meta;
		return (true);
		}
	}

template<> inline bool _Fgetc(wchar_t& _Wchar, _Filet *_File)
	{	// get a wchar_t element from a C stream
	wint_t _Meta;
	if ((_Meta = ::fgetwc(_File)) == WEOF)
		return (false);
	else
		{	// got one, convert to wchar_t
		_Wchar = (wchar_t)_Meta;
		return (true);
		}
	}

 #ifdef _CRTBLD_NATIVE_WCHAR_T
template<> inline bool _Fgetc(unsigned short& _Wchar, _Filet *_File)
	{	// get an unsigned short element from a C stream
	wint_t _Meta;
	if ((_Meta = ::fgetwc(_File)) == WEOF)
		return (false);
	else
		{	// got one, convert to unsigned short
		_Wchar = (unsigned short)_Meta;
		return (true);
		}
	}
 #endif /* _CRTBLD_NATIVE_WCHAR_T */

		// TEMPLATE FUNCTION _Fputc
template<class _Elem> inline
	bool _Fputc(_Elem _Ch, _Filet *_File)
	{	// put an element to a C stream
	return (fwrite(&_Ch, 1, sizeof (_Elem), _File) == sizeof (_Elem));
	}

template<> inline bool _Fputc(char _Byte, _Filet *_File)
	{	// put a char element to a C stream
	return (fputc(_Byte, _File) != EOF);
	}

template<> inline bool _Fputc(wchar_t _Wchar, _Filet *_File)
	{	// put a wchar_t element to a C stream
	return (::fputwc(_Wchar, _File) != WEOF);
	}

 #ifdef _CRTBLD_NATIVE_WCHAR_T
template<> inline bool _Fputc(unsigned short _Wchar, _Filet *_File)
	{	// put an unsigned short element to a C stream
	return (::fputwc(_Wchar, _File) != WEOF);
	}
 #endif /* _CRTBLD_NATIVE_WCHAR_T */

		// TEMPLATE FUNCTION _Ungetc
template<class _Elem> inline
	bool _Ungetc(const _Elem& _Ch, _Filet *_File)
	{	// put back an arbitrary element to a C stream (always fail)
	return (false);
	}

template<> inline bool _Ungetc(const char& _Byte, _Filet *_File)
	{	// put back a char element to a C stream
	return (ungetc((unsigned char)_Byte, _File) != EOF);
	}

template<> inline bool _Ungetc(const signed char& _Byte, _Filet *_File)
	{	// put back a signed char element to a C stream
	return (ungetc((unsigned char)_Byte, _File) != EOF);
	}

template<> inline bool _Ungetc(const unsigned char& _Byte, _Filet *_File)
	{	// put back an unsigned char element to a C stream
	return (ungetc(_Byte, _File) != EOF);
	}

template<> inline bool _Ungetc(const wchar_t& _Wchar, _Filet *_File)
	{	// put back a wchar_t element to a C stream
	return (::ungetwc(_Wchar, _File) != WEOF);
	}

 #ifdef _CRTBLD_NATIVE_WCHAR_T
template<> inline bool _Ungetc(const unsigned short& _Wchar, _Filet *_File)
	{	// put back an unsigned short element to a C stream
	return (::ungetwc(_Wchar, _File) != WEOF);
	}
 #endif /* _CRTBLD_NATIVE_WCHAR_T */

		// TEMPLATE CLASS basic_filebuf
template<class _Elem,
	class _Traits>
	class basic_filebuf
		: public basic_streambuf<_Elem, _Traits>
	{	// stream buffer associated with a C stream
public:
	typedef basic_filebuf<_Elem, _Traits> _Myt;
	typedef basic_streambuf<_Elem, _Traits> _Mysb;
	typedef typename _Traits::state_type _Myst;
#if !defined(_WIN32_WCE)
	typedef codecvt<_Elem, char, typename _Traits::state_type> _Cvt;
#endif

	virtual __CLR_OR_THIS_CALL ~basic_filebuf()
		{	// destroy the object
		if (_Closef)
			close();
		}

	__CLR_OR_THIS_CALL basic_filebuf(_Filet *_File = 0)
		: _Mysb()
		{	// construct from pointer to C stream
		_Init(_File, _Newfl);
		}

	typedef _Elem char_type;
	typedef _Traits traits_type;
	typedef typename _Traits::int_type int_type;
	typedef typename _Traits::pos_type pos_type;
	typedef typename _Traits::off_type off_type;

	__CLR_OR_THIS_CALL basic_filebuf(_Uninitialized)
		: _Mysb(_Noinit)
		{	// construct uninitialized
		}

	enum _Initfl
		{	// reasons for a call to _Init
		_Newfl, _Openfl, _Closefl};

	bool __CLR_OR_THIS_CALL is_open() const
		{	// test if C stream has been opened
		return (_Myfile != 0);
		}

	_Myt *__CLR_OR_THIS_CALL open(const char *_Filename,
		ios_base::openmode _Mode,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a C stream with specified mode
		_Filet *_File;
		if (_Myfile != 0 || (_File = _Fiopen(_Filename, _Mode, _Prot)) == 0)
			return (0);	// open failed

		_Init(_File, _Openfl);
#if !defined(_WIN32_WCE)
		_Initcvt((_Cvt *)&_USE(_Mysb::getloc(), _Cvt));
#endif
		return (this);	// open succeeded
		}

	_Myt *__CLR_OR_THIS_CALL open(const char *_Filename, ios_base::open_mode _Mode)
		{	// open a C stream with specified mode (old style)
		return (open(_Filename, (ios_base::openmode)_Mode));
		}

	_Myt *__CLR_OR_THIS_CALL open(const wchar_t *_Filename,
		ios_base::openmode _Mode,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		_Filet *_File;
		if (_Myfile != 0 || (_File = _Fiopen(_Filename, _Mode, _Prot)) == 0)
			return (0);	// open failed

		_Init(_File, _Openfl);
#if !defined(_WIN32_WCE)
		_Initcvt((_Cvt *)&_USE(_Mysb::getloc(), _Cvt));
#endif
		return (this);	// open succeeded
		}

	_Myt *__CLR_OR_THIS_CALL open(const wchar_t *_Filename, ios_base::open_mode _Mode)
		{	// open a wide-named C stream (old style) -- EXTENSION
		return (open(_Filename, (ios_base::openmode)_Mode));
		}

#ifdef _NATIVE_WCHAR_T_DEFINED
	_Myt * __CLR_OR_THIS_CALL open(const unsigned short *_Filename,
		ios_base::openmode _Mode,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		_Filet *_File;
		if (_Myfile != 0 || (_File = _Fiopen(_Filename, _Mode, _Prot)) == 0)
			return (0);	// open failed

		_Init(_File, _Openfl);
#if !defined(_WIN32_WCE)
		_Initcvt((_Cvt *)&_USE(_Mysb::getloc(), _Cvt));
#endif
		return (this);	// open succeeded
		}

	_Myt * __CLR_OR_THIS_CALL open(const unsigned short *_Filename, ios_base::open_mode _Mode)
		{	// open a wide-named C stream (old style) -- EXTENSION
		return (open(_Filename, (ios_base::openmode)_Mode));
		}
 #endif /* _NATIVE_WCHAR_T_DEFINED */

	_Myt *__CLR_OR_THIS_CALL close()
		{	// close the C stream
		_Myt *_Ans = this;
		if (_Myfile == 0)
			_Ans = 0;
		else
			{	// put any homing sequence and close file
			if (!_Endwrite())
				_Ans = 0;
			if (fclose(_Myfile) != 0)
				_Ans = 0;
			}
		_Init(0, _Closefl);
		return (_Ans);
		}

protected:
	virtual int_type __CLR_OR_THIS_CALL overflow(int_type _Meta = _Traits::eof())
		{	// put an element to stream
		if (_Traits::eq_int_type(_Traits::eof(), _Meta))
			return (_Traits::not_eof(_Meta));	// EOF, return success code
		else if (_Mysb::pptr() != 0
			&& _Mysb::pptr() < _Mysb::epptr())
			{	// room in buffer, store it
			*_Mysb::_Pninc() = _Traits::to_char_type(_Meta);
			return (_Meta);
			}
		else if (_Myfile == 0)
			return (_Traits::eof());	// no open C stream, fail
#if defined(_WIN32_WCE)
		else
#else
		else if (_Pcvt == 0)
#endif
			return (_Fputc(_Traits::to_char_type(_Meta), _Myfile)
				? _Meta : _Traits::eof());	// no codecvt facet, put as is
#if !defined(_WIN32_WCE)
		else
			{	// put using codecvt facet
			const int _STRING_INC = 8;
			const _Elem _Ch = _Traits::to_char_type(_Meta);
			const _Elem *_Src;
			char *_Dest;

			string _Str(_STRING_INC, '\0');
			for (; ; )
				switch (_Pcvt->out(_State,
					&_Ch, &_Ch + 1, _Src,
					&*_Str.begin(), &*_Str.begin() + _Str.size(), _Dest))
				{	// test result of converting one element
				case codecvt_base::partial:
				case codecvt_base::ok:
					{	// converted something, try to put it out
					size_t _Count = _Dest - &*_Str.begin();
					if (0 < _Count && _Count !=
						fwrite(&*_Str.begin(), 1, _Count, _Myfile))
						return (_Traits::eof());	// write failed

					_Wrotesome = true;	// write succeeded
					if (_Src != &_Ch)
						return (_Meta);	// converted whole element

					if (0 < _Count)
						;
					else if (_Str.size() < 4 * _STRING_INC)
						_Str.append(_STRING_INC, '\0');	// try with more space
					else
						return (_Traits::eof());	// conversion failed
					break;
					}

				case codecvt_base::noconv:
					return (_Fputc(_Ch, _Myfile) ? _Meta
						: _Traits::eof());	// no conversion, put as is

				default:
					return (_Traits::eof());	// conversion failed
				}
			}
#endif
		}

	virtual int_type __CLR_OR_THIS_CALL pbackfail(int_type _Meta = _Traits::eof())
		{	// put an element back to stream
		if (_Mysb::gptr() != 0
			&& _Mysb::eback() < _Mysb::gptr()
			&& (_Traits::eq_int_type(_Traits::eof(), _Meta)
			|| _Traits::eq_int_type(_Traits::to_int_type(_Mysb::gptr()[-1]),
				_Meta)))
			{	// just back up position
			_Mysb::_Gndec();
			return (_Traits::not_eof(_Meta));
			}
		else if (_Myfile == 0 || _Traits::eq_int_type(_Traits::eof(), _Meta))
			return (_Traits::eof());	// no open C stream or EOF, fail
		else if (
#if !defined(_WIN32_WCE)
			_Pcvt == 0 && 
#endif
			_Ungetc(_Traits::to_char_type(_Meta), _Myfile))
			return (_Meta);	// no facet and unget succeeded, return
#pragma warning(push)
#pragma warning(disable: 6237 6239)
		/* prefast noise VSW 489858 */
		else if (1 < sizeof (_Elem) && _Mysb::gptr() != &_Mychar)
#pragma warning(pop)
			{	// putback to _Mychar
			_Mychar = _Traits::to_char_type(_Meta);
			_Mysb::setg(&_Mychar, &_Mychar, &_Mychar + 1);
			return (_Meta);
			}
		else
			return (_Traits::eof());	// nowhere to put back
		}

	virtual int_type __CLR_OR_THIS_CALL underflow()
		{	// get an element from stream, but don't point past it
		int_type _Meta;
		if (_Mysb::gptr() != 0
			&& _Mysb::gptr() < _Mysb::egptr())
			return (_Traits::to_int_type(*_Mysb::gptr()));	// return buffered
		else if (_Traits::eq_int_type(_Traits::eof(), _Meta = uflow()))
			return (_Meta);	// uflow failed, return EOF
		else
			{	// get a char, don't point past it
			pbackfail(_Meta);
			return (_Meta);
			}
		}

	virtual int_type __CLR_OR_THIS_CALL uflow()
		{	// get an element from stream, point past it
		if (_Mysb::gptr() != 0
			&& _Mysb::gptr() < _Mysb::egptr())
			return (_Traits::to_int_type(
				*_Mysb::_Gninc()));	// return buffered
		else if (_Myfile == 0)
			return (_Traits::eof());	// no open C stream, fail
#if defined(_WIN32_WCE)
		else
#else
		else if (_Pcvt == 0)
#endif
			{	// no codecvt facet, just get it
			_Elem _Ch;
			return (_Fgetc(_Ch, _Myfile) ? _Traits::to_int_type(_Ch)
				: _Traits::eof());
			}
#if !defined(_WIN32_WCE)
		else
			{	// build string until codecvt succeeds
			string _Str;

			for (; ; )
				{	// get using codecvt facet
				_Elem _Ch, *_Dest;
				const char *_Src;
				ptrdiff_t _Nleft;
				int _Meta = fgetc(_Myfile);

				if (_Meta == EOF)
					return (_Traits::eof());	// partial char?

				_Str.append(1, (char)_Meta);	// append byte and convert
				switch (_Pcvt->in(_State,
					&*_Str.begin(), &*_Str.begin() + _Str.size(), _Src,
					&_Ch, &_Ch + 1, _Dest))
					{	// test result of converting one element
				case codecvt_base::partial:
				case codecvt_base::ok:
					if (_Dest != &_Ch)
						{	// got an element, put back excess and deliver it
						for (_Nleft = &*_Str.begin() + _Str.size() - _Src;
							0 < _Nleft; )
							ungetc(_Src[--_Nleft], _Myfile);
						return (_Traits::to_int_type(_Ch));
						}
					else
						_Str.erase((size_t)0,	// partial, discard used input
							(size_t)(_Src - &*_Str.begin()));
					break;

				case codecvt_base::noconv:
					if (_Str.size() < sizeof (_Elem))
						break;	// no conversion, but need more chars

					_CRT_SECURE_MEMCPY(&_Ch,sizeof (_Elem), &*_Str.begin(),
						sizeof (_Elem));	// copy raw bytes to element
					return (_Traits::to_int_type(_Ch));	// return result

				default:
					return (_Traits::eof());	// conversion failed
					}
				}
			}
#endif
		}

	virtual pos_type __CLR_OR_THIS_CALL seekoff(off_type _Off,
		ios_base::seekdir _Way,
		ios_base::openmode =
			(ios_base::openmode)(ios_base::in | ios_base::out))
		{	// change position by _Off
		fpos_t _Fileposition;

		if (_Mysb::gptr() == &_Mychar	// something putback
			&& _Way == ios_base::cur	// a relative seek
#if !defined(_WIN32_WCE)
			&& _Pcvt == 0	// not converting
#endif
			)
			_Off -= (off_type)sizeof (_Elem);	// back up over _Elem bytes

		if (_Myfile == 0 || !_Endwrite()
			|| (_Off != 0 || _Way != ios_base::cur)
				&& fseek(_Myfile, (long)_Off, _Way) != 0
			|| fgetpos(_Myfile, &_Fileposition) != 0)
			return (pos_type(_BADOFF));	// report failure

		if (_Mysb::gptr() == &_Mychar)
			_Mysb::setg(&_Mychar, &_Mychar + 1,
				&_Mychar + 1);	// discard any putback
		return (_POS_TYPE_FROM_STATE(pos_type, _State,
			_Fileposition));	// return new position
		}

	virtual pos_type __CLR_OR_THIS_CALL seekpos(pos_type _Pos,
		ios_base::openmode =
			(ios_base::openmode)(ios_base::in | ios_base::out))
		{	// change position to _Pos
		fpos_t _Fileposition = _POS_TYPE_TO_FPOS_T(_Pos);
		off_type _Off = (off_type)_Pos - _FPOSOFF(_Fileposition);

		if (_Myfile == 0 || !_Endwrite()
			|| fsetpos(_Myfile, &_Fileposition) != 0
			|| _Off != 0 && fseek(_Myfile, (long)_Off, SEEK_CUR) != 0
			|| fgetpos(_Myfile, &_Fileposition) != 0)
			return (pos_type(_BADOFF));	// report failure

		_State = _POS_TYPE_TO_STATE(_Pos);

		if (_Mysb::gptr() == &_Mychar)
			_Mysb::setg(&_Mychar, &_Mychar + 1,
				&_Mychar + 1);	// discard any putback
		return (_POS_TYPE_FROM_STATE(pos_type, _State,
			_Fileposition));	// return new position
		}

	virtual _Mysb *__CLR_OR_THIS_CALL setbuf(_Elem *_Buffer, streamsize _Count)
		{	// offer _Buffer to C stream
		if (_Myfile == 0 || setvbuf(_Myfile, (char *)_Buffer,
			_Buffer == 0 && _Count == 0 ? _IONBF : _IOFBF,
			_Count * sizeof (_Elem)) != 0)
			return (0);	// failed
		else
			{	// new buffer, reinitialize pointers
			_Init(_Myfile, _Openfl);
			return (this);
			}
		}

	virtual int __CLR_OR_THIS_CALL sync()
		{	// synchronize C stream with external file
		return (_Myfile == 0
			|| _Traits::eq_int_type(_Traits::eof(), overflow())
			|| 0 <= fflush(_Myfile) ? 0 : -1);
		}
#if !defined(_WIN32_WCE)
	virtual void __CLR_OR_THIS_CALL imbue(const locale& _Loc)
		{	// set locale to argument (capture nontrivial codecvt facet)
		_Initcvt((_Cvt *)&_USE(_Loc, _Cvt));
		}
#endif

	void __CLR_OR_THIS_CALL _Init(_Filet *_File, _Initfl _Which)
		{	// initialize to C stream _File after {new, open, close}
		__PURE_APPDOMAIN_GLOBAL static _Myst _Stinit;	// initial state
		_Closef = _Which == _Openfl;
		_Wrotesome = false;

		_Mysb::_Init();	// initialize stream buffer base object

 #ifndef _IORCNT
  #define _IORCNT	_IOCNT	/* read and write counts are the same */
  #define _IOWCNT _IOCNT
 #endif /* _IORCNT */


		/* prefast noise VSW 489858 */
#if !defined(_WIN32_WCE)
	// TODO If we don't figure out the internal HFILE implementation, make sure we document the side effects of this change
#pragma warning(push)
#pragma warning(disable: 6240)
		if (_File != 0 && sizeof (_Elem) == 1)
#pragma warning(pop)
			{	// point inside C stream with [first, first + count) buffer
			_THROW(invalid_argument, "unsuppored parameter on CE");
			_Elem **_Pb = (_Elem **)&_File->_IOBASE;
			_Elem **_Pn = (_Elem **)&_File->_IOPTR;
			int *_Nr = (int *)&_File->_IORCNT;
			int *_Nw = (int *)&_File->_IOWCNT;
			_Mysb::_Init(_Pb, _Pn, _Nr, _Pb, _Pn, _Nw);
			}
#endif
		_Myfile = _File;
		_State = _Stinit;
#if !defined(_WIN32_WCE)
		_Pcvt = 0;	// pointer to codecvt facet
#endif
		}

	bool __CLR_OR_THIS_CALL _Endwrite()
		{	// put shift to initial conversion state, as needed
#if !defined(_WIN32_WCE)
		if (_Pcvt == 0 || !_Wrotesome)
#endif
			return (true);
#if !defined(_WIN32_WCE)
		else
			{	// may have to put
			const int _STRING_INC = 8;
			char *_Dest;
			if (_Traits::eq_int_type(_Traits::eof(), overflow()))
				return (false);

			string _Str(_STRING_INC, '\0');
			for (; ; )
				switch (_Pcvt->unshift(_State,
					&*_Str.begin(), &*_Str.begin() + _Str.size(), _Dest))
				{	// test result of homing conversion
				case codecvt_base::ok:
					_Wrotesome = false;	// homed successfully

				case codecvt_base::partial:	// fall through
					{	// put any generated bytes
					size_t _Count = _Dest - &*_Str.begin();
					if (0 < _Count && _Count !=
						fwrite(&*_Str.begin(), 1, _Count, _Myfile))
						return (false);	// write failed
					if (!_Wrotesome)
						return (true);
					if (_Count == 0)
						_Str.append(_STRING_INC, '\0');	// try with more space
					break;
					}

				case codecvt_base::noconv:
					return (true);	// nothing to do

				default:
					return (false);	// conversion failed
				}
			}
#endif
		}

#if !defined(_WIN32_WCE)
	void __CLR_OR_THIS_CALL _Initcvt(_Cvt *_Newpcvt)
		{	// initialize codecvt pointer
		if (_Newpcvt->always_noconv())
			_Pcvt = 0;	// nothing to do
		else
			{	// set up for nontrivial codecvt facet
			_Pcvt = _Newpcvt;
			_Mysb::_Init();	// reset any buffering
			}
		}
#endif /* !_WIN32_WCE */

private:
#if !defined(_WIN32_WCE)
	_Cvt *_Pcvt;	// pointer to codecvt facet (may be null)
#endif
	_Elem _Mychar;	// putback character, when _Ungetc fails
	bool _Wrotesome;	// true if homing sequence may be needed
	typename _Traits::state_type _State;	// current conversion state
	bool _Closef;	// true if C stream must be closed
	_Filet *_Myfile;	// pointer to C stream
	};


 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

  #ifdef __FORCE_INSTANCE
template class _CRTIMP2_PURE basic_filebuf<char,
	char_traits<char> >;
template class _CRTIMP2_PURE basic_filebuf<wchar_t,
	char_traits<wchar_t> >;

   #ifdef _CRTBLD_NATIVE_WCHAR_T
template class _CRTIMP2_PURE basic_filebuf<unsigned short,
	char_traits<unsigned short> >;
   #endif /* _CRTBLD_NATIVE_WCHAR_T */

  #endif /* __FORCE_INSTANCE */

 #endif /* _DLL_CPPLIB */

		// TEMPLATE CLASS basic_ifstream
template<class _Elem,
	class _Traits>
	class basic_ifstream
		: public basic_istream<_Elem, _Traits>
	{	// input stream associated with a C stream
public:
	typedef basic_ifstream<_Elem, _Traits> _Myt;
	typedef basic_filebuf<_Elem, _Traits> _Myfb;
	typedef basic_ios<_Elem, _Traits> _Myios;

	__CLR_OR_THIS_CALL basic_ifstream()
		: basic_istream<_Elem, _Traits>(&_Filebuffer)
		{	// construct unopened
		}

	explicit __CLR_OR_THIS_CALL basic_ifstream(const char *_Filename,
		ios_base::openmode _Mode = ios_base::in,
		int _Prot = (int)ios_base::_Openprot)
		: basic_istream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with named file and specified mode
		if (_Filebuffer.open(_Filename, _Mode | ios_base::in, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	explicit __CLR_OR_THIS_CALL basic_ifstream(const wchar_t *_Filename,
		ios_base::openmode _Mode = ios_base::in,
		int _Prot = (int)ios_base::_Openprot)
		: basic_istream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with wide-named file -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::in, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

 #ifdef _NATIVE_WCHAR_T_DEFINED
	explicit __CLR_OR_THIS_CALL basic_ifstream(const unsigned short *_Filename,
		ios_base::openmode _Mode = ios_base::in,
		int _Prot = (int)ios_base::_Openprot)
		: basic_istream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with wide-named file -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::in, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}
 #endif /* _NATIVE_WCHAR_T_DEFINED */

	explicit __CLR_OR_THIS_CALL basic_ifstream(_Filet *_File)
		: basic_istream<_Elem, _Traits>(&_Filebuffer),
			_Filebuffer(_File)
		{	// construct with specified C stream
		}
	void __CLR_OR_THIS_CALL open(const wchar_t *_Filename,
		ios_base::openmode _Mode = ios_base::in,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::in, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const wchar_t *_Filename, ios_base::open_mode _Mode)
		{	// open wide-named file (old style) -- EXTENSION
		open(_Filename, (ios_base::openmode)_Mode);
		}

 #ifdef _NATIVE_WCHAR_T_DEFINED
	void __CLR_OR_THIS_CALL open(const unsigned short *_Filename,
		ios_base::openmode _Mode = ios_base::in,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::in, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const unsigned short *_Filename, ios_base::open_mode _Mode)
		{	// open wide-named file (old style) -- EXTENSION
		open(_Filename, (ios_base::openmode)_Mode);
		}
 #endif /* _NATIVE_WCHAR_T_DEFINED */

	virtual __CLR_OR_THIS_CALL ~basic_ifstream()
		{	// destroy the object
		}

	_Myfb *__CLR_OR_THIS_CALL rdbuf() const
		{	// return pointer to file buffer
		return ((_Myfb *)&_Filebuffer);
		}

	bool __CLR_OR_THIS_CALL is_open() const
		{	// test if C stream has been opened
		return (_Filebuffer.is_open());
		}

	void __CLR_OR_THIS_CALL open(const char *_Filename,
		ios_base::openmode _Mode = ios_base::in,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a C stream with specified mode
		if (_Filebuffer.open(_Filename, _Mode | ios_base::in, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const char *_Filename, ios_base::open_mode _Mode)
		{	// open named file with specified mode (old style)
		open(_Filename, (ios_base::openmode)_Mode);
		}

	void __CLR_OR_THIS_CALL close()
		{	// close the C stream
		if (_Filebuffer.close() == 0)
			_Myios::setstate(ios_base::failbit);
		}

private:
	_Myfb _Filebuffer;	// the file buffer
	};

 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

  #ifdef __FORCE_INSTANCE
template class _CRTIMP2_PURE basic_ifstream<char,
	char_traits<char> >;
template class _CRTIMP2_PURE basic_ifstream<wchar_t,
	char_traits<wchar_t> >;

   #ifdef _CRTBLD_NATIVE_WCHAR_T
template class _CRTIMP2_PURE basic_ifstream<unsigned short,
	char_traits<unsigned short> >;
   #endif /* _CRTBLD_NATIVE_WCHAR_T */

  #endif /* __FORCE_INSTANCE */

 #endif /* _DLL_CPPLIB */

		// TEMPLATE CLASS basic_ofstream
template<class _Elem,
	class _Traits>
	class basic_ofstream
		: public basic_ostream<_Elem, _Traits>
	{	// output stream associated with a C stream
public:
	typedef basic_ofstream<_Elem, _Traits> _Myt;
	typedef basic_filebuf<_Elem, _Traits> _Myfb;
	typedef basic_ios<_Elem, _Traits> _Myios;

	__CLR_OR_THIS_CALL basic_ofstream()
		: basic_ostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct unopened
		}

	explicit __CLR_OR_THIS_CALL basic_ofstream(const char *_Filename,
		ios_base::openmode _Mode = ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		: basic_ostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with named file and specified mode
		if (_Filebuffer.open(_Filename, _Mode | ios_base::out, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	explicit __CLR_OR_THIS_CALL basic_ofstream(const wchar_t *_Filename,
		ios_base::openmode _Mode = ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		: basic_ostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with wide-named file -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::out, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

 #ifdef _NATIVE_WCHAR_T_DEFINED
	explicit __CLR_OR_THIS_CALL basic_ofstream(const unsigned short *_Filename,
		ios_base::openmode _Mode = ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		: basic_ostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with wide-named file -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::out, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}
 #endif /* _NATIVE_WCHAR_T_DEFINED */

	explicit __CLR_OR_THIS_CALL basic_ofstream(_Filet *_File)
		: basic_ostream<_Elem, _Traits>(&_Filebuffer),
			_Filebuffer(_File)
		{	// construct with specified C stream
		}

	virtual __CLR_OR_THIS_CALL ~basic_ofstream()
		{	// destroy the object
		}

	_Myfb *__CLR_OR_THIS_CALL rdbuf() const
		{	// return pointer to file buffer
		return ((_Myfb *)&_Filebuffer);
		}

	bool __CLR_OR_THIS_CALL is_open() const
		{	// test if C stream has been opened
		return (_Filebuffer.is_open());
		}

	void __CLR_OR_THIS_CALL open(const wchar_t *_Filename,
		ios_base::openmode _Mode = ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::out, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const wchar_t *_Filename, ios_base::open_mode _Mode)
		{	// open a wide-named C stream (old style) -- EXTENSION
		open(_Filename, (ios_base::openmode)_Mode);
		}

 #ifdef _NATIVE_WCHAR_T_DEFINED
	void __CLR_OR_THIS_CALL open(const unsigned short *_Filename,
		ios_base::openmode _Mode = ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode | ios_base::out, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const unsigned short *_Filename, ios_base::open_mode _Mode)
		{	// open wide-named file (old style) -- EXTENSION
		open(_Filename, (ios_base::openmode)_Mode);
		}
 #endif /* _NATIVE_WCHAR_T_DEFINED */

	void __CLR_OR_THIS_CALL open(const char *_Filename,
		ios_base::openmode _Mode = ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a C stream with specified mode
		if (_Filebuffer.open(_Filename, _Mode | ios_base::out, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const char *_Filename, ios_base::open_mode _Mode)
		{	// open a C stream with specified mode (old style)
		open(_Filename, (ios_base::openmode)_Mode);
		}

	void __CLR_OR_THIS_CALL close()
		{	// close the C stream
		if (_Filebuffer.close() == 0)
			_Myios::setstate(ios_base::failbit);
		}

private:
	_Myfb _Filebuffer;	// the file buffer
	};

 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

  #ifdef __FORCE_INSTANCE
template class _CRTIMP2_PURE basic_ofstream<char,
	char_traits<char> >;
template class _CRTIMP2_PURE basic_ofstream<wchar_t,
	char_traits<wchar_t> >;

   #ifdef _CRTBLD_NATIVE_WCHAR_T
template class _CRTIMP2_PURE basic_ofstream<unsigned short,
	char_traits<unsigned short> >;
   #endif /* _CRTBLD_NATIVE_WCHAR_T */

  #endif /* __FORCE_INSTANCE */

 #endif /* _DLL_CPPLIB */

		// TEMPLATE CLASS basic_fstream
template<class _Elem,
	class _Traits>
	class basic_fstream
		: public basic_iostream<_Elem, _Traits>
	{	// input/output stream associated with a C stream
public:
	typedef basic_fstream<_Elem, _Traits> _Myt;
	typedef basic_ios<_Elem, _Traits> _Myios;
	typedef _Elem char_type;
	typedef _Traits traits_type;
	typedef typename _Traits::int_type int_type;
	typedef typename _Traits::pos_type pos_type;
	typedef typename _Traits::off_type off_type;

	__CLR_OR_THIS_CALL basic_fstream()
		: basic_iostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct unopened
		}

	explicit __CLR_OR_THIS_CALL basic_fstream(const char *_Filename,
		ios_base::openmode _Mode = ios_base::in | ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		: basic_iostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with named file and specified mode
		if (_Filebuffer.open(_Filename, _Mode, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	explicit __CLR_OR_THIS_CALL basic_fstream(const wchar_t *_Filename,
		ios_base::openmode _Mode = ios_base::in | ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		: basic_iostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with wide-named file -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

 #ifdef _NATIVE_WCHAR_T_DEFINED
	explicit __CLR_OR_THIS_CALL basic_fstream(const unsigned short *_Filename,
		ios_base::openmode _Mode = ios_base::in | ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		: basic_iostream<_Elem, _Traits>(&_Filebuffer)
		{	// construct with wide-named file -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}
 #endif /* _NATIVE_WCHAR_T_DEFINED */

	explicit __CLR_OR_THIS_CALL basic_fstream(_Filet *_File)
		: basic_iostream<_Elem, _Traits>(&_Filebuffer),
			_Filebuffer(_File)
		{	// construct with specified C stream
		}

	void __CLR_OR_THIS_CALL open(const wchar_t *_Filename,
		ios_base::openmode _Mode = ios_base::in | ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const wchar_t *_Filename, ios_base::open_mode _Mode)
		{	// open a wide-named C stream (old style) -- EXTENSION
		open(_Filename, (ios_base::openmode)_Mode);
		}

 #ifdef _NATIVE_WCHAR_T_DEFINED
	void __CLR_OR_THIS_CALL open(const unsigned short *_Filename,
		ios_base::openmode _Mode = ios_base::in | ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a wide-named C stream -- EXTENSION
		if (_Filebuffer.open(_Filename, _Mode, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const unsigned short *_Filename, ios_base::open_mode _Mode)
		{	// open a wide-named C stream (old style) -- EXTENSION
		open(_Filename, (ios_base::openmode)_Mode);
		}
 #endif /* _NATIVE_WCHAR_T_DEFINED */

	virtual __CLR_OR_THIS_CALL ~basic_fstream()
		{	// destroy the object
		}

	basic_filebuf<_Elem, _Traits> *__CLR_OR_THIS_CALL rdbuf() const
		{	// return pointer to file buffer
		return ((basic_filebuf<_Elem, _Traits> *)&_Filebuffer);
		}

	bool __CLR_OR_THIS_CALL is_open() const
		{	// test if C stream has been opened
		return (_Filebuffer.is_open());
		}

	void __CLR_OR_THIS_CALL open(const char *_Filename,
		ios_base::openmode _Mode = ios_base::in | ios_base::out,
		int _Prot = (int)ios_base::_Openprot)
		{	// open a C stream with specified mode
		if (_Filebuffer.open(_Filename, _Mode, _Prot) == 0)
			_Myios::setstate(ios_base::failbit);
		}

	void __CLR_OR_THIS_CALL open(const char *_Filename, ios_base::open_mode _Mode)
		{	// open a C stream with specified mode (old style)
		open(_Filename, (ios_base::openmode)_Mode);
		}

	void __CLR_OR_THIS_CALL close()
		{	// close the C stream
		if (_Filebuffer.close() == 0)
			_Myios::setstate(ios_base::failbit);
		}

private:
	basic_filebuf<_Elem, _Traits> _Filebuffer;	// the file buffer
	};

 #if defined(_DLL_CPPLIB) && !defined(_M_CEE_PURE)

  #ifdef __FORCE_INSTANCE
template class _CRTIMP2_PURE basic_fstream<char,
	char_traits<char> >;
template class _CRTIMP2_PURE basic_fstream<wchar_t,
	char_traits<wchar_t> >;

   #ifdef _CRTBLD_NATIVE_WCHAR_T
template class _CRTIMP2_PURE basic_fstream<unsigned short,
	char_traits<unsigned short> >;
   #endif /* _CRTBLD_NATIVE_WCHAR_T */

  #endif /* __FORCE_INSTANCE */

 #endif /* _DLL_CPPLIB */
_STD_END

#ifdef  _MSC_VER
  #pragma warning(default: 4127)

#pragma warning(pop)
#pragma pack(pop)
#endif  /* _MSC_VER */

#endif /* RC_INVOKED */
#endif /* _FSTREAM_ */

/*
 * Copyright (c) 1992-2005 by P.J. Plauger.  ALL RIGHTS RESERVED.
 * Consult your license regarding permissions and restrictions.
 V4.05:0009 */
