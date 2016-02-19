// $Id: driver.h 17 2007-08-19 18:51:39Z tb $ 	
/** \file driver.h Declaration of the example::Driver class. */

#ifndef BOOKSHELFPARSER_DRIVER_H
#define BOOKSHELFPARSER_DRIVER_H

#include "BookshelfDataBase.h"

/** The example namespace is used to encapsulate the three parser classes
 * example::Parser, example::Scanner and example::Driver */
namespace BookshelfParser {

	using std::cout;
	using std::endl;
	using std::cerr;
	using std::string; 
	using std::vector;
	using std::pair;
	using std::make_pair;
	using std::ostringstream;

/** The Driver class brings together all components. It creates an instance of
 * the Parser and Scanner classes and connects them. Then the input stream is
 * fed into the scanner object and the parser gets it's token
 * sequence. Furthermore the driver object is available in the grammar rules as
 * a parameter. Therefore the driver class contains a reference to the
 * structure into which the parsed data is saved. */
class Driver
{
public:
    /// construct a new parser driver context
    Driver(BookshelfDataBase& db);

    /// enable debug output in the flex scanner
    bool trace_scanning;

    /// enable debug output in the bison parser
    bool trace_parsing;

    /// stream name (file or input stream) used for error messages.
    string streamname;

    /** Invoke the scanner and parser for a stream.
     * @param in	input stream
     * @param sname	stream name for error messages
     * @return		true if successfully parsed
     */
    bool parse_stream(std::istream& in,
		      const string& sname = "stream input");

    /** Invoke the scanner and parser on an input string.
     * @param input	input string
     * @param sname	stream name for error messages
     * @return		true if successfully parsed
     */
    bool parse_string(const string& input,
		      const string& sname = "string stream");

    /** Invoke the scanner and parser on a file. Use parse_stream with a
     * std::ifstream if detection of file reading errors is required.
     * @param filename	input file name
     * @return		true if successfully parsed
     */
    bool parse_file(const string& filename);

    // To demonstrate pure handling of parse errors, instead of
    // simply dumping them on the standard error output, we will pass
    // them to the driver using the following two member functions.

    /** Error handling with associated line number. This can be modified to
     * output the error e.g. to a dialog box. */
    void error(const class location& l, const string& m);

    /** General error handling. This can be modified to output the error
     * e.g. to a dialog box. */
    void error(const string& m);

    /** Pointer to the current lexer instance, this is used to connect the
     * parser to the scanner. It is used in the yylex macro. */
    class Scanner* lexer;

    /** Reference to the database filled during parsing of the
     * expressions. */
    BookshelfDataBase& m_db;

    // .nodes file 
    void numNodeTerminalsCbk(int, int);
    void terminalEntryCbk(string&, int, int);
    void nodeEntryCbk(string&, int, int, string&);
    void nodeEntryCbk(string&, int, int);
    // .nets file 
    void numNetCbk(int);
    void numPinCbk(int);
    void netPinEntryCbk(string&, char, double, double, double, double, string&);
    void netPinEntryCbk(string&, char, double, double, double=0.0, double=0.0);
    void netNameAndDegreeCbk(string&, int);
    void netEntryCbk();
    // .pl file 
    void plNodeEntryCbk(string&, double, double, string&, string&);
    void plNodeEntryCbk(string&, double, double, string&);
    // .scl file 
    void sclNumRows(int);
    void sclCoreRowStart(string const&);
    void sclCoreRowCoordinate(int);
    void sclCoreRowHeight(int);
    void sclCoreRowSitewidth(int);
    void sclCoreRowSitespacing(int);
    void sclCoreRowSiteorient(int);
    void sclCoreRowSitesymmetry(int);
    void sclCoreRowSubRowOrigin(int);
    void sclCoreRowNumSites(int);
    void sclCoreRowEnd();
    // .wts file 
    // .aux file 
    void auxCbk(string&, vector<string>&);

    vector<string> const& bookshelfFiles() const {return m_vBookshelfFiles;}
protected:
	// use as a stack for node and pin pairs in a net 
	// because net_cbk_pin will be called before net_cbk_name
	Row m_row;
	Net m_net;
    vector<string> m_vBookshelfFiles; ///< store bookshelf files except .aux 
};

// top api for BookshelfParser
bool read(BookshelfDataBase& db, const string& auxFile);

} // namespace example

#endif // EXAMPLE_DRIVER_H
