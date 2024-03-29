# Configuration file for the Sphinx documentation builder.

# -- Project information

# If you want smaller code font size
# from sphinx.highlighting import PygmentsBridge
# from pygments.formatters.latex import LatexFormatter

# class CustomLatexFormatter(LatexFormatter):
#     def __init__(self, **options):
#         super(CustomLatexFormatter, self).__init__(**options)
#         self.verboptions = r"formatcom=\footnotesize"

# PygmentsBridge.latex_formatter = CustomLatexFormatter

project = 'LeetSolve'
copyright = '2024, Nhut Nguyen'
author = 'Nhut Nguyen'

version = '1.2.3'

# -- General configuration

extensions = [
    'myst_parser',
    'sphinx.ext.duration',
    'sphinx.ext.doctest',
    'sphinx.ext.autodoc',
    'sphinx.ext.autosummary',
    'sphinx.ext.intersphinx',
    'sphinx.ext.mathjax',
]

myst_enable_extensions = ["dollarmath", "amsmath", "smartquotes"]

intersphinx_mapping = {
    'python': ('https://docs.python.org/3/', None),
    'sphinx': ('https://www.sphinx-doc.org/en/master/', None),
}
intersphinx_disabled_domains = ['std']

templates_path = ['_templates']

# master_doc = 'index_10'
master_doc = 'index_book1'
exclude_patterns = ['*/index_*.rst']

# -- Options for HTML output

html_theme = "furo"
html_logo = "img/logo_name.svg"
pygments_style = 'bw' # bw stands for black and white, for print
html_theme_options = {
    # 'logo_only': True,
    "sidebar_hide_name": True,
    # 'nosidebar': True,
    # "announcement": "Support my work by buying this book <a href='https://store.nhutnguyen.com/l/leetsolve'  target='_blank'>here</a>!", 
}

source_suffix = {
    '.rst': 'restructuredtext',
    '.md': 'markdown',
}

latex_elements = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',
    # 'sphinxsetup': 'hmargin={1in,1in}, vmargin={1in,1in}',

    # The font size ('10pt', '11pt' or '12pt').
    #
    'pointsize': '11pt',

    # Additional stuff for the LaTeX preamble.
    #
    'preamble': r'''
    \usepackage{charter}
    \usepackage[defaultsans]{lato}
    \usepackage{inconsolata}
    \definecolor{TitleColor}{rgb}{0,0,0}
    \definecolor{InnerLinkColor}{rgb}{0,0,0}
    \usepackage[paperwidth=7.5in,paperheight=9.25in]{geometry}
    \addto\captionsenglish{\renewcommand{\contentsname}{Contents}}
    \setcounter{tocdepth}{1}
    ''',
    # uncomment these in preamble for print
    # \definecolor{TitleColor}{rgb}{0,0,0}
    # \definecolor{InnerLinkColor}{rgb}{0,0,0}


    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',        
}
# turn on footnote for print book
latex_show_urls = 'footnote'

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
# latex_documents = [
#     (master_doc, 'leetsolve.tex', '10 Classic Coding Challenges',
#      'Nhut Nguyen, Ph. D.', 'howto'),
# ]
latex_documents = [
    (master_doc, 'leetsolve.tex', 'The Problem Solver\'s Guide To Coding',
     'Nhut Nguyen, Ph. D.', 'book'),
]
latex_docclass = {
   'book': 'book',
}
