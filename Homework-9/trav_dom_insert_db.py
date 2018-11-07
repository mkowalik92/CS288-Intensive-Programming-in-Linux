from xml.dom.minidom import parse, parseString
import mysql.connector
import sys

def lst_to_dict( lst ):
    rtn_dict = { "num":lst[0], "name":lst[1], "symbol":lst[2], "volume":lst[3].replace( ",", "" ), "price":lst[4].replace( "$", "" ), "pricechange":lst[5], "perchange":lst[6] }
    return rtn_dict
    
def get_text( lst, node_count ):
    if ( node_count == 1 ):
        temp_lst = lst[1].childNodes
        value = temp_lst[0].nodeValue.replace( "\n", "" )
        value_split = value.replace( ")", "" ).split("(")
        value_split[0] = value_split[0].rstrip()
        return value_split
    else:
        value = lst[0].nodeValue
        value_lst = [ value ]
        return value_lst
    
dom = parse( sys.argv[1] ) # doc
lst = dom.childNodes # go passed doc to show <html>
lst_1 = lst[0].childNodes # ele - go inside <html>

lst_2 = lst_1[1].childNodes # ele - go inside <body
lst_2_filter_nl = list( filter( lambda y : y.nodeType == 1, lst_2 ) )

lst_3 = lst_2_filter_nl[4].childNodes # ele - go inside <div style
lst_3_filter_nl = list( filter( lambda y : y.nodeType == 1, lst_3 ) )

lst_4 = lst_3_filter_nl[2].childNodes # ele - go inside <div id
lst_4_filter_nl = list( filter( lambda y : y.nodeType == 1, lst_4 ) )

lst_5 = lst_4_filter_nl[2].childNodes # ele - go inside <div class
lst_5_filter_nl = list( filter( lambda y : y.nodeType == 1, lst_5 ) )

trs = lst_5_filter_nl[2].childNodes # goal - ele - go inside <table

tr_count = 0
stock_dict_lst = []
extracted_values = []
for stock in trs:
    if ( tr_count == 0 ):
        tr_count = tr_count + 1
        continue
    else:
        stock_nodes = stock.childNodes
        node_count = 0
        for node in stock_nodes:
            extracted_values = extracted_values + get_text( node.childNodes, node_count )
            node_count = node_count + 1
        node_count = 0
    #print( extracted_values )
    stock_dict_lst.append( lst_to_dict( extracted_values ) )
    extracted_values = []

#print( stock_dict_lst )
connection = mysql.connector.connect( user = "cs288", password = "1q1r0s3t", host = "127.0.0.1", database = "stocks" )
cursor = connection.cursor()
create_stock_table = "CREATE TABLE " + sys.argv[1].replace( ".xhtml", "" ) + " (num INT(4), name VARCHAR(90), symbol VARCHAR(10) PRIMARY KEY, volume INT(15), price DOUBLE(10,2), pricechange DOUBLE(10,2), perchange DOUBLE(10,2));"
#print( create_stock_table )
cursor.execute( create_stock_table )
for stock in stock_dict_lst:
    insert_stock_table = "INSERT INTO " + sys.argv[1].replace( ".xhtml", "" ) + " (num, name, symbol, volume, price, pricechange, perchange) VALUES (" + stock["num"] + ", '" + stock["name"].replace( "'", "" ) + "', '" + stock["symbol"] + "', " + stock["volume"] + ", " + stock["price"] + ", " + stock["pricechange"] + ", " + stock["perchange"] + ");"
    cursor.execute( insert_stock_table )
    #print( insert_stock_table )
connection.commit()
connection.close()

