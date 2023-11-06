#include <iostream>
#include <random>
#include <vector>
#include "qte.h"
#include "implicits.h"
#include "ui_interface.h"
#include "sphere.h"
#include "fusion.h"
#include "extrusion.h"
#include "node.h"
#include "mathematics.h"
#include "tore.h"
#include "cylindre.h"
#include "capsule.h"
#include "roundbox.h"
#include "roundcone.h"
#include "translation.h"
#include "intersection.h"
#include "scale.h"
#include "displacement.h"
#include "sphere_erosion.h"
#include "bezier.h"
#include "mesh.h"

MainWindow::MainWindow() : QMainWindow(), uiw(new Ui::Assets)
{
	// Chargement de l'interface
    uiw->setupUi(this);

	// Chargement du GLWidget
	meshWidget = new MeshWidget;
	QGridLayout* GLlayout = new QGridLayout;
	GLlayout->addWidget(meshWidget, 0, 0);
	GLlayout->setContentsMargins(0, 0, 0, 0);
    uiw->widget_GL->setLayout(GLlayout);

	// Creation des connect
	CreateActions();

	meshWidget->SetCamera(Camera(Vector(10, 0, 0), Vector(0.0, 0.0, 0.0)));
}

MainWindow::~MainWindow()
{
	delete meshWidget;
}

void MainWindow::CreateActions()
{
	// Buttons
    connect(uiw->boxMesh, SIGNAL(clicked()), this, SLOT(BonhommeDeNeige()));
    connect(uiw->sphereImplicit, SIGNAL(clicked()), this, SLOT(ColonneRodin()));
	connect(uiw->Erosion, SIGNAL(clicked()), this, SLOT(Erosion()));
	connect(uiw->Bezier, SIGNAL(clicked()), this, SLOT(Bezier()));
	connect(uiw->Revolution, SIGNAL(clicked()), this, SLOT(Revolution()));
    connect(uiw->resetcameraButton, SIGNAL(clicked()), this, SLOT(ResetCamera()));
    connect(uiw->wireframe, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_1, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));
    connect(uiw->radioShadingButton_2, SIGNAL(clicked()), this, SLOT(UpdateMaterial()));

	// Widget edition
	connect(meshWidget, SIGNAL(_signalEditSceneLeft(const Ray&)), this, SLOT(editingSceneLeft(const Ray&)));
	connect(meshWidget, SIGNAL(_signalEditSceneRight(const Ray&)), this, SLOT(editingSceneRight(const Ray&)));
}

void MainWindow::editingSceneLeft(const Ray&)
{
}

void MainWindow::editingSceneRight(const Ray&)
{
}

void MainWindow::Revolution()
{
	std::vector<Vector> m = {Vector(0.0,0.0,0.0),Vector(0.0,1.0,0.0),Vector(0.3,1.2,0.0),Vector(0.6,1.4,0.0),Vector(0.9,1.45,0.0),Vector(1.0,1.5,0.0),Vector(1.5,1.6,0.0),Vector(1.6,1.4,0.0),Vector(1.63,1.366,0.0),Vector(1.66,1.333,0.0),Vector(1.7,1.3,0.0),Vector(1.66,1.236,0.0),Vector(1.63,1.233,0.0),Vector(1.6,1.2,0.0),Vector(1.4,1.2,0.0),Vector(1.36,1.166,0.0),Vector(1.33,1.133,0.0),Vector(1.3,1.1,0.0),Vector(1.33,1.066,0.0),Vector(1.36,1.033,0.0),Vector(1.4,1.0,0.0),Vector(2.0,1.1,0.0),Vector(2.5,1.2,0.0),Vector(3.0,1.3,0.0),Vector(3.5,1.4,0.0),Vector(4.0,1.5,0.0),Vector(4.5,1.6,0.0),Vector(4.8,1.65,0.0),Vector(4.82,1.655,0.0),Vector(4.84,1.66,0.0),Vector(4.86,1.665,0.0),Vector(4.88,1.67,0.0),Vector(4.9,1.68,0.0),Vector(5.0,2.0,0.0)};
	Vector start = Vector(0.0,0.0,0.0);
	Vector end = Vector(5.0,0.0,0.0);
	Bezier_Rev revolution_bezier(m, start, end, 'x');

	Mesh BezierMesh;
	BezierMesh = revolution_bezier.GetMesh(40);

	QString folderPath = "C:\\Users\\marti\\Desktop\\3A_ECL\\Master\\Modelisation geometrique\\Pion.obj";
	QString fileName = "Pion";
	BezierMesh.SaveObj(folderPath,fileName);

	std::vector<Color> cols;
	cols.resize(BezierMesh.Vertexes());
	for (size_t i = 0; i < cols.size(); i++)
	cols[i] = Color(0.99, 0.01, 0.01);

	meshColor = MeshColor(BezierMesh, cols, BezierMesh.VertexIndexes());
	UpdateGeometry();
}
void MainWindow::Bezier()
{	
	// std::vector<Vector> n;
	// Vector v = Vector(0,0,0);
	// float t = 0.0;
	// float delta_t = 0.1;
	// float z = 0.0;
	// for (int i = 0; i < 100; i++) {
	// 	n.push_back(v);
	// 	if (t < 1.0) {
    //     z = t;
    // 	} else if (t < 2.0) {
    //     z = 2.0 - t;
    // 	} else if (t < 3.0) {
    //     z = t - 3.0;
    // 	} else {
    //     z = 4.0 - t;
    // 	}
   	// 	t += delta_t;
	// 	v.operator+=(Vector(0.05,0.0,z));
	// }
	std::vector<Vector> n = {Vector(0.0,0.0,0.0),Vector(0.2,0.0,0.4),Vector(0.4,0.0,0.8),Vector(0.6,0.0,0.9),Vector(0.8,0.0,1.0),Vector(1.0,0.0,1.0),Vector(1.2,0.0,1.0),Vector(1.4,0.0,0.9),Vector(1.6,0.0,0.8),Vector(1.8,0.0,0.4),Vector(2.0,0.0,0.0),Vector(2.2,0.0,-0.4),Vector(2.4,0.0,-0.8),Vector(2.6,0.0,-0.9),Vector(2.8,0.0,-1.0),Vector(3.0,0.0,-1.0),Vector(3.2,0.0,-1.0),Vector(3.4,0.0,-0.9),Vector(3.6,0.0,-0.8),Vector(3.8,0.0,-0.4),Vector(4.0,0.0,0.0)};
	std::vector<Vector> m = {Vector(0.0,0.0,0.0),Vector(0.0,0.5,0.0),Vector(0.0,1.0,0.0),Vector(0.0,1.5,0.0),Vector(0.0,2.0,0.0),Vector(0.0,2.5,0.0),Vector(0.0,3.0,0.0)};
	Bezier_class courbe_bezier(n, m);

	Mesh BezierMesh;
	BezierMesh = courbe_bezier.GetMesh(static_cast<int>(n.size()),static_cast<int>(m.size()));

	QString folderPath = "C:\\Users\\marti\\Desktop\\3A_ECL\\Master\\Modelisation geometrique\\TinyMesh\\AppTinyMesh\\Source\\Bezier.obj";
	QString fileName = "Bezier";
	BezierMesh.SaveObj(folderPath,fileName);

	std::vector<Color> cols;
	cols.resize(BezierMesh.Vertexes());
	for (size_t i = 0; i < cols.size(); i++)
	cols[i] = Color(0.99, 0.9196, 0.8228);

	meshColor = MeshColor(BezierMesh, cols, BezierMesh.VertexIndexes());
	UpdateGeometry();
}

void MainWindow::ColonneRodin()
{
	// Primitives : 
	Cylindre cylindre(Vector(0.0,0.0,6.0),Vector(4.0,4.0,0),1.0);
	Cylindre base_haute(Vector(0.0,0.0,6.0),Vector(4.0,4.0,0),10.0);
	Cylindre base_basse(Vector(0.0,0.0,6.0),Vector(4.0,4.0,0),10.0);

	// Transformations affines :
	Scale base_b(&base_basse,0.15f);
	Scale base_h(&base_haute,0.15f);
	Translation final_base_b(&base_b,Vector(4,4,-0.9));
	Translation final_base_h(&base_h,Vector(-0.5,-0.5,5.8));

	Displacement c(&cylindre);

	// Opérateurs Binaires :
	Union base(&c, &final_base_b ,0.75);
	Union colonne(&base, &final_base_h ,0.75);

	Arbre arbre;
	arbre.racine = &colonne;

	AnalyticScalarField implicit;
	Mesh sphereMesh;
	implicit.Polygonize(170, sphereMesh, Box(10.0), arbre);

  std::vector<Color> cols;
  cols.resize(sphereMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.99, 0.9196, 0.8228);

  meshColor = MeshColor(sphereMesh, cols, sphereMesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::BonhommeDeNeige()
{
// création de SDF :
	Sphere sphere1(Vector(-4,-4,0.0),3.0);
	Sphere sphere2(Vector(0.0,0.0,0.0),4.0);
	Capsule brasdroit(Vector(0.0,0.0,0.0),Vector(0.0,-6.0,0),0.5);
	Capsule brasgauche(Vector(0.0,0.0,0.0),Vector(-6.0,0.0,0),0.5);
	Cylindre nez(Vector(-3.9,-3.9,-2.0),Vector(-4.25,-4.25,-4.5),0.25);
	Cylindre c1(Vector(-3.9,-3.9,-2.0),Vector(-4.25,-4.25,-4.5),0.25);
	Cylindre c2(Vector(-3.9,-3.9,-2.0),Vector(-4.25,-4.25,-4.5),0.25);

	Translation oeil_droit(&c1, Vector(-1.5,0,0));
	Translation oeil_gauche(&c2, Vector(0,-1.5,0));

	Union merge_sphere(&sphere1, &sphere2, 0.75);
	Union merge_bras_gauche(&merge_sphere, &brasdroit, 0.25);
	Union merge_bras_droit(&merge_bras_gauche, &brasgauche, 0.25);
	Union assemblage_nez(&merge_bras_droit, &nez, 0.5);
	Extrusion assemblage_oeil(&oeil_droit, &assemblage_nez, 0.25);
	Extrusion bonhomme_neige(&oeil_gauche, &assemblage_oeil, 0.25);


// Création de l'arbre : 
	Arbre arbre;
	arbre.racine = &bonhomme_neige;
	// arbre.racine = erosion;
	
	AnalyticScalarField implicit;
	Mesh sphereMesh;
	implicit.Polygonize(120, sphereMesh, Box(10.0), arbre);

  std::vector<Color> cols;
  cols.resize(sphereMesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.99, 0.99, 0.99);

  meshColor = MeshColor(sphereMesh, cols, sphereMesh.VertexIndexes());
  UpdateGeometry();
}


void MainWindow::Erosion()
{
// Erosion : 
	std::random_device rd;
  	std::mt19937 gen(rd());
  	std::uniform_real_distribution<float> dis(-1.8f, 1.8f);
	std::uniform_real_distribution<float> dis2(0.01f, 0.4f);
	std::uniform_real_distribution<float> dis3(0.1f, 4.1f);

	Sphere sphere1(Vector(0,0,0.0),2.0);
	Vector p[500];
	Union erosion[500];
	Sphere sph[500];
	Sphere init1(Vector(0,0,-2),0.1f);
	Sphere init2(Vector(0.5,0.5,-1.8),0.1f);
	erosion[0]=Union(&init1,&init2,0);
	for (int i=1; i<300; i++) {
		p[i] = intersection(Vector(dis(gen),dis(gen),-2.1),Vector(0,0,dis3(gen)),&sphere1,1);
		sph[i] = Sphere(p[i],dis2(gen));
		erosion[i]=Union(&sph[i],&erosion[i-1],0);
	}
	Extrusion erode(&erosion[299],&sphere1,0.99f);
// Création de l'arbre : 
	Arbre arbre;
	arbre.racine = &erode;
	
	AnalyticScalarField implicit;
	Mesh mesh;
	implicit.Polygonize(100, mesh, Box(10.0), arbre);

  std::vector<Color> cols;
  cols.resize(mesh.Vertexes());
  for (size_t i = 0; i < cols.size(); i++)
    cols[i] = Color(0.99, 0.99, 0.99);

  meshColor = MeshColor(mesh, cols, mesh.VertexIndexes());
  UpdateGeometry();
}

void MainWindow::UpdateGeometry()
{
	meshWidget->ClearAll();
	meshWidget->AddMesh("BoxMesh1", meshColor);

    uiw->lineEdit->setText(QString::number(meshColor.Vertexes()));
    uiw->lineEdit_2->setText(QString::number(meshColor.Triangles()));

	UpdateMaterial();
}

void MainWindow::UpdateMaterial()
{
    meshWidget->UseWireframeGlobal(uiw->wireframe->isChecked());

    if (uiw->radioShadingButton_1->isChecked())
		meshWidget->SetMaterialGlobal(MeshMaterial::Normal);
	else
		meshWidget->SetMaterialGlobal(MeshMaterial::Color);
}

void MainWindow::ResetCamera()
{
	meshWidget->SetCamera(Camera(Vector(-10.0), Vector(0.0)));
}
