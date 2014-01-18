import sys
import features

GETPRICE_TEMPLATE = "http://download.finance.yahoo.com/d/quotes.csv?s={0}&f=l1"

def main(argv=None):

    #Process Arglist
    if argv is None:
        argv = sys.argv
    ticker_symbols = argv[1:]

    #Create vector of feature extraction functions
    featureFuncs = [
            features.getCurrPrice,
            ]

    #Extract features into output object
    for ticker_symbol in ticker_symbols:
        print features.getCurrPrice(ticker_symbol)

if __name__ == "__main__":
    sys.exit(main())
