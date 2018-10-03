# Question 6.1

class Graph:
	def __init__(self, size):
		self.size = size # number of nodes
		self.adjacencyMatrix = [[0 for col in xrange(self.size)] for row in xrange(self.size)]
	
	def addEdge(self, src, dest):
		self.adjacencyMatrix[src-1][dest-1] = 1
	
	def maxHeight(self):
		# Use DFS to find maximum height
		self.maxHeights = [0 for i in xrange(self.size)]
		for node in xrange(self.size):
			self.visited = [0 for j in xrange(self.size)]
			self.maxHeights[node] = self.maxHeightHelper(node)
		return max(self.maxHeights)
	
	def maxHeightHelper(self, node):
		self.visited[node] = 1
		height = -1
		for adjacentNode in xrange(self.size):
			if self.adjacencyMatrix[node][adjacentNode] and not self.visited[adjacentNode]:
				height = max(height, self.maxHeightHelper(adjacentNode))
		return height + 1

def Q6(filename):
	print "Running " + filename + "..."
	
	# Open input file and output file
	try:
		inputFile = open(filename, 'r')
	except IOError:
		print filename + " doesn't exist.\n"
		return
	outputFile = open("Q6.1_" + filename[3:], 'w')
	
	# Read number of nodes from input file
	numOfNodes = int(inputFile.readline())
	
	# Read topologies from input file
	for topology in inputFile:
		
		# Create tree
		tree = Graph(numOfNodes)
		for edge in [int(edge) for edge in topology.split()]:
			tree.addEdge(edge/10, edge%10)
		
		# Solution - tree with max height of not more than 3
		# Write solution to output file
		if tree.maxHeight() <= 3:
			outputFile.write(topology)
			
	# Close input file and output file
	inputFile.close()
	outputFile.close()
	
	print "Finish running " + filename + ".\n"

Q6("Q1_5node6links.txt")
Q6("Q1_6node7link.txt")
Q6("Q1_6node8link.txt")
Q6("Q1_7node6link.txt")
print "The output files are in the project folder."