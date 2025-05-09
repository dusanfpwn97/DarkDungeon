

def EmitSampleCategory(category, file):
	if not FirstCategory:
		file.write("""
			]
		},""")
	file.write("""
		{
			"category": "%s",
			"cards": [
""" % category)

	
def EmitSampleEntry(tokens, fileHandle):
	title = tokens[1]
	short_desc = tokens[2]
	link = tokens[4]
	image = tokens[5]
	file = tokens[6]
	if not FirstCategoryItem:
		fileHandle.write(',\n')
	
	filename = "templates_flow/%s.json" % file
	fileHandle.write("""				{
					"title": "%s",
					"desc": "%s",
					"image": "detail/thumb/%s_t",
					"link": "pages/%s"
				}""" % (title, short_desc, image, filename))
	
	
def CreateSampleFile(tokens, ExecType):
	title = tokens[1]
	long_desc = tokens[3]
	link = tokens[4]
	image = tokens[5]
	file = tokens[6]
	video = tokens[7]
	build_on_clone = tokens[8]
	dep1 = tokens[9]
	dep1_title = tokens[10]
	dep2 = tokens[11]
	dep2_title = tokens[12]
	
	dot_idx = link.find('.')
	path1 = link[:dot_idx]	# PackageName
	path2 = link	# PackageName.ObjectName
	
	filename = "templates_flow/%s.json" % file
	with open(filename, 'w') as file:
		file.write("""{
  "title": "%s",
  "layout": "Details",
  "desc": "%s",
  "image": "detail/%s",
  "actions": [""" % (title, long_desc, image))
		FirstEntry = True
		if path1 != '':
			FirstEntry = False
	  
			# Print out the actions
			file.write("""
    {
      "type": "%s",
      "path": "%s"
    }""" % (ExecType, path1))

		if not FirstEntry:
			file.write(",")
			
		if video != "":
			file.write("""
    {
      "type": "Video",
      "path": "%s"
    }""" % video)
	
		if dep1 != "":
			file.write(""",
	{
      "type": "LauncherURL",
	  "path": "%s",
	  "title": "%s",
	  "width": 72
    }""" % (dep1, dep1_title))
	
		if dep2 != "":
			file.write(""",
	{
      "type": "LauncherURL",
	  "path": "%s",
	  "title": "%s",
	  "width": 72
    }""" % (dep2, dep2_title))
	
		file.write("""
  ]
}""")


FirstCategory = True
FirstCategoryItem = True
with open('flowgraph_templates_data.csv') as dataFile:
	with open('flowgraph_templates.json', 'w') as sf:
		sf.write("""{
	"title": "Graph Templates",
	"layout": "CardGrid",
	"description": "Create a new graph from one of these templates",
	"showCategoryTitles": true,
	"categories": 
	[""")
		ExecType = "CloneGridFlow"
		for line in dataFile.readlines():
			tokens = line.split('\t')
			category = tokens[0]
			if category != '':
				EmitSampleCategory(category, sf)
				FirstCategory = False
				FirstCategoryItem = True
				if category.startswith("Grid"):
					ExecType = "CloneGridFlow"
				elif category.startswith("Snap"):
					ExecType = "CloneSnapFlow"
					
			else:
				EmitSampleEntry(tokens, sf)
				CreateSampleFile(tokens, ExecType)
				FirstCategoryItem = False
		
		sf.write("""
			]
		}
	]
}
""")
