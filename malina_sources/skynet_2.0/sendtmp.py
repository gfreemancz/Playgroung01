
import urllib
import sys


# print urllib.urlopen('http://gfrscb.wz.cz/htdocs/savetmp.php?sensor=venku&temper=0.1')



# print 'Number of arguments:', len(sys.argv), 'arguments.'
# print 'Argument List:', sys.argv[1], sys.argv[2]

url = "http://gfrscb.wz.cz/htdocs/savetmp.php?sensor="+sys.argv[1]+"&temper="+sys.argv[2]+"&time="+sys.argv[3]

urllib.urlopen(url)
