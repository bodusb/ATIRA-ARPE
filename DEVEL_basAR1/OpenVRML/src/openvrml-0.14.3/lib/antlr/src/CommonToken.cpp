/* ANTLR Translator Generator
 * Project led by Terence Parr at http://www.jGuru.com
 * Software rights: http://www.antlr.org/RIGHTS.html
 *
 * $Id: CommonToken.cpp,v 1.1.1.1 2003/04/06 22:26:27 braden Exp $
 */

#include "antlr/CommonToken.hpp"
#include "antlr/String.hpp"

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
namespace antlr {
#endif

CommonToken::CommonToken() : Token(), line(1), col(1), text("")
{}

CommonToken::CommonToken(int t, const ANTLR_USE_NAMESPACE(std)string& txt)
	: Token(t), line(1), col(1), text(txt)
{}

CommonToken::CommonToken(const ANTLR_USE_NAMESPACE(std)string& s)
	: Token(), line(1), col(1), text(s)
{}

ANTLR_USE_NAMESPACE(std)string CommonToken::toString() const
{
	return "[\""+getText()+"\",<"+type+">,line="+line+",column="+col+"]";
}

RefToken CommonToken::factory()
{
	return RefToken(new CommonToken);
}

#ifdef ANTLR_CXX_SUPPORTS_NAMESPACE
}
#endif

