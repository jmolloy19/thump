#include <stockwatch/get_stock_symbols.hpp>

/**
 * Parses a string for stock symbols, and pushes each valid symbol into a vector.
 * @param stock_symbols pointer to vector that stock symbols will be pushed into
 * @param nyse		   if true, also gets stock symbols on NYSE. Else, just NASDAQ
 */
void GetStockSymbols(std::vector<std::string>* stock_symbols, bool nyse)
{
    std::string stock_symbol_buffer;
	
    if(!RequestStockSymbols(&stock_symbol_buffer, nyse))
	{
		std::cerr << "Error getting stock symbols\n";
		exit(-1);
	}

	std::string::const_iterator it, 
						        begin = stock_symbol_buffer.begin(), 
						        end = stock_symbol_buffer.end();
						   
	it = find(begin, end, '\n') + 1; 					// Skip header line
	
	while(it != end)
	{
		std::string symbol(it, find(it, end, '|'));		// Parses line for stock symbol
		if(IsValidStockSymbol(symbol))						
			stock_symbols->push_back(symbol);
		it = find(it, end, '\n') + 1;
	}
	
	std::cout << "Total # of stock symbols extracted: " << stock_symbols->size() << "\n\n";
}

/**
 * Verifies whether the string is a valid stock symbol.
 * @param symbol string to verify
 */
bool IsValidStockSymbol(const std::string& symbol)
{
	if(symbol.size() > 5)									// Exclude any symbol greater than 5 characters
		return false;
	else
	{
		std::string::const_iterator it;
		for(it = symbol.begin(); it != symbol.end(); it++)	// Exclude any symbol containing characters outside range 'A' - 'Z'
			if(*it < 65 || *it > 90)					    
				return false;
		return true;
	}
}

/**
 * This function is the callback function that gets called by libcurl as soon as there 
 * is data received that needs to be saved.
 * @param contents points to delivered data 
 * @param nmemb    the size of delievered data,
 * @param size     is always 1
 * @param userp    points to where delivered data will be written
 */
static size_t RequestStockSymbolsCallback(void *contents, size_t size, size_t nmemb, void *userp)
{	
	try
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
	}
	catch (std::bad_alloc& err)
	{
		std::cerr << "Memory allocation failed. Error: " << err.what();
		return 0;
	}
    return size * nmemb;
}

/**
 * Makes a HTTP request for the files containing stock symbols and writes it to a string.
 * @param stock_symbol_buffer string that stock symbols will be written to
 * @param nyse 	     		  if true, also gets stock symbols on NYSE. Else, just NASDAQ
 */
bool RequestStockSymbols(std::string* stock_symbol_buffer, bool nyse)
{
	CURL *curl;
	CURLcode res;
	
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl) 
    {
	  	stock_symbol_buffer->clear();
	    curl_easy_setopt(curl, CURLOPT_URL, "ftp://ftp.nasdaqtrader.com/symboldirectory/nasdaqlisted.txt");   // Set URL to be used in HTTP request (list of NASDAQ stocks)
	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, RequestStockSymbolsCallback);							  // Set RequestStockSymbolsCallback as ptr to callback function
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, stock_symbol_buffer);										  // Set stock_symbol_buffer as ptr to where delivered data will be written
	    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);												  // Disable curl verifying the authenticity of a peer's SSL certificate
	    res = curl_easy_perform(curl);
	    if(res != CURLE_OK)
		{
	    	std::cerr << curl_easy_strerror(res);
			return false;
		}
	    else if(nyse)
	    {
	    	curl_easy_setopt(curl, CURLOPT_URL, "ftp://ftp.nasdaqtrader.com/symboldirectory/otherlisted.txt"); // Change URL to be used in second request (List of NYSE stocks)
	     	res = curl_easy_perform(curl);
	    	if(res != CURLE_OK)
			{
	    		std::cerr << curl_easy_strerror(res);
				return false;
			}
	    	else
	    	{
	    		curl_easy_cleanup(curl);
	    		curl_global_cleanup();
			}
		}
		return true;
    }
	else
	{
		std::cerr << "Error initializing curl\n";
		return false;
	}
		
}