#pragma once

#include <QWidget>
#include "enums.h"

#include <qcombobox.h>
#include <qlabel.h>
#include <qgridlayout.h>
#include <qstackedlayout.h>
#include <qcheckbox.h>
#include<qspinbox.h>
#include"color_picker.h"

#include "property_macros.h"

#include <qjsonobject.h>
#include <qfile.h>
#include <qdir.h>
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qbytearray.h>

/*! @brief Widget which show the the materials properties from lists of Qt3DExtras materials.
   Also  write current values to json file and read file on pograms start if such json file exist.
   Provide signals on every property changed.
   */
class property_material : public QWidget
{
	Q_OBJECT

public:
	/// @brief default constructor
	/// @param parentPath previous path to store json configs
	/// @param parent parent QWidget
	property_material(QString parentPath, QWidget *parent = Q_NULLPTR);

	/// @brief default destructor
	~property_material();

private:
	QComboBox* combobox_material;
	QString parentPath_;

	ADD_JSON_LOADER(phong)
	ADD_JSON_LOADER(diffuse_map)
	ADD_JSON_LOADER(diffuse_specular_map)
	ADD_JSON_LOADER(diffuse_specular)
	ADD_JSON_LOADER(gooch)
	ADD_JSON_LOADER(metal_rough)
	ADD_JSON_LOADER(morph_phong)
	ADD_JSON_LOADER(normal_diffuse_map)
	ADD_JSON_LOADER(normal_diffuse_specular_map)
	ADD_JSON_LOADER(phong_alpha)
	ADD_JSON_LOADER(texture)
	ADD_JSON_LOADER(current_material_index)

public:

	/// @brief plain structure to store signal name and signal data
	template <typename T>
	struct 	delayed_emit
	{
		QString signal_name;
		T signal_data;
	};
	/// @brief list of all signals and their datas type of double
	std::vector<delayed_emit<double>> e_vec_func_double;
	/// @brief list of all signals and their datas type of int
	std::vector<delayed_emit<int>> e_vec_func_int;
	/// @brief list of all signals and their datas type of QColor
	std::vector<delayed_emit<QColor>> e_vec_func_QColor;

	/// @brief initialisation function to call in constructor and set all data from json to different properties in widget window
	void send_initialization_data()
	{
		qDebug() << Q_FUNC_INFO << " CALLED !!! ";
		//emit property_mesh_type_signal(combobox_mesh->currentIndex());

		QMetaObject::invokeMethod(this,
			"property_material_type_signal",
			Qt::QueuedConnection,
			Q_ARG(int, combobox_material->currentIndex()));

		for (auto& e : e_vec_func_double) {
			qDebug() << "BEGIN::QMetaObject::invokeMethod(" << e.signal_name.toStdString().data() << "," << e.signal_data << ") - invoke data  ";
			bool result = QMetaObject::invokeMethod(this,
				e.signal_name.toStdString().data(),
				Qt::QueuedConnection,
				Q_ARG(double, e.signal_data));

			qDebug() << "END::QMetaObject::invokeMethod(" << e.signal_name.toStdString().data() << "," << e.signal_data << ")invoke result is: " << result;
		}

		for (auto& e : e_vec_func_int)
		{
			qDebug() << "BEGIN::QMetaObject::invokeMethod(" << e.signal_name.toStdString().data() << "," << e.signal_data << ") - invoke data";
			bool result = QMetaObject::invokeMethod(this,
				e.signal_name.toStdString().data(),
				Qt::QueuedConnection,
				Q_ARG(int, e.signal_data));

			qDebug() << "END::QMetaObject::invokeMethod(" << e.signal_name.toStdString().data() << "," << e.signal_data << ")invoke result is: " << result;
		}

		for (auto& e : e_vec_func_QColor)
		{
			qDebug() << "BEGIN::QMetaObject::invokeMethod(" << e.signal_name.toStdString().data() << "," << e.signal_data << ") - invoke data";
			bool result = QMetaObject::invokeMethod(this,
				e.signal_name.toStdString().data(),
				Qt::QueuedConnection,
				Q_ARG(QColor, e.signal_data));

			qDebug() << "END::QMetaObject::invokeMethod(" << e.signal_name.toStdString().data() << "," << e.signal_data << ")invoke result is: " << result;
		}
	};


signals:

	/// @brief material type signal emits on combobox changes
	void property_material_type_signal(int);
	//PHONG
	ADD_SIGNAL_FOR_ENTITY(material, phong, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, phong, diffuse, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, phong, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, phong, specular, QColor);
	//

	//DIFFUSE_MAP
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_map, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_map, specular, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_map, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_map, texture_scale, double);
	//

	//DIFFUSE_SPECULAR_MAP
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular_map, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular_map, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular_map, texture_scale, double);
	//

	//DIFFUSE_SPECULAR
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular, alpha_blending, bool);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular, diffuse, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular, specular, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, diffuse_specular, texture_scale, double);
	//
	
	//GOOCH
	ADD_SIGNAL_FOR_ENTITY(material, gooch, specular, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, gooch, warm, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, gooch, diffuse, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, gooch, cool, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, gooch, alpha, double);
	ADD_SIGNAL_FOR_ENTITY(material, gooch, beta, double);
	ADD_SIGNAL_FOR_ENTITY(material, gooch, shininess, double);
	//

	//METAL_ROUGH
	ADD_SIGNAL_FOR_ENTITY(material, metal_rough, base_color, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, metal_rough, texture_scale, double);
	//

	//MORPH_PHONG
	ADD_SIGNAL_FOR_ENTITY(material, morph_phong, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, morph_phong, diffuse, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, morph_phong, specular, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, morph_phong, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, morph_phong, interpolator, double);
	//

	//NORMAL_DIFFUSE_MAP
	ADD_SIGNAL_FOR_ENTITY(material, normal_diffuse_map, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, normal_diffuse_map, specular, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, normal_diffuse_map, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, normal_diffuse_map, texture_scale, double);
	//

	//NORMAL_DIFFUSE_SPECULAR_MAP
	ADD_SIGNAL_FOR_ENTITY(material, normal_diffuse_specular_map, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, normal_diffuse_specular_map, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, normal_diffuse_specular_map, texture_scale, double);
	//

	//PHONG_ALPHA
	ADD_SIGNAL_FOR_ENTITY(material, phong_alpha, ambient, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, phong_alpha, diffuse, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, phong_alpha, specular, QColor);
	ADD_SIGNAL_FOR_ENTITY(material, phong_alpha, shininess, double);
	ADD_SIGNAL_FOR_ENTITY(material, phong_alpha, alpha, double);
	//

	//TEXTURE
	ADD_SIGNAL_FOR_ENTITY(material, texture, alpha_blending, bool);
	//

	

};
