#include "recogniser.h"

constexpr int WIDTH_A4_LIST = 1500; // С€РёСЂРёРЅР° Р»РёСЃС‚Р° РІ РїРёРєСЃРµР»СЏС…
constexpr int HEIGHT_A4_LIST = 1000; // РІС‹СЃРѕС‚Р° Р»РёСЃС‚Р° РІ РїРёРєСЃРµР»СЏС…
constexpr int WIDTH_TABLE_LIST = 1300; // С€РёСЂРёРЅР° С‚Р°Р±Р»РёС†С‹ РІ РїРёРєСЃРµР»СЏС…
constexpr int HEIGHT_TABLE_LIST = 700; // РІС‹СЃРѕС‚Р° С‚Р°Р±Р»РёС†С‹ РІ РїРёРєСЃРµР»СЏС…
constexpr int TABLE_ROWS = 22;
constexpr int TABLE_COLS = 10;

void resize_to_wsize(Mat& img) 
{
 resize(img, img, Size(2048, 1536)); 
}

// РЅР°С…РѕР¶РґРµРЅРёРµ СѓРіР»РѕРІ Р»РёСЃС‚Р° РЅР° С„РѕС‚РѕРіСЂР°С„РёРё
vector<Point> find_list_corners(Mat& img_)
{
 int BORDER_SIZE = 5; // С‚РѕР»С‰РёРЅР° РіСЂР°РЅРёС†С‹ С‚Р°Р±Р»РёС†С‹ РІ РїРёРєСЃРµР»СЏС…
 
 adaptiveThreshold(img_, img_, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 115, 4); // Р°РґР°РїС‚РёРІРЅРѕРµ РїРѕСЂРѕРіРѕРІРѕРµ РїСЂРµРѕР±СЂР°Р·РѕРІР°РЅРёРµ РґР»СЏ СЌР»РµРјРµРЅС‚РѕРІ РјР°СЃСЃРёРІР°
 /* img_ вЂ” РёСЃС…РѕРґРЅС‹Р№ РјР°СЃСЃРёРІ(РёР·РѕР±СЂР°Р¶РµРЅРёРµ), img_ вЂ” С†РµР»РµРІРѕР№ РјР°СЃСЃРёРІ
 ADAPTIVE_THRESH_GAUSSIAN_C вЂ” РїРёРєСЃРµР»Рё РѕРєСЂРµСЃС‚РЅРѕСЃС‚Рё СѓРјРЅРѕР¶Р°СЋС‚СЃСЏ РЅР° РІРµСЃРѕРІРѕР№ РєРѕСЌС„С„РёС†РёРµРЅС‚ (РІР·РІРµС€РёРІР°СЋС‚СЃСЏ) РІ СЃРѕРѕС‚РІРµС‚СЃС‚РІРёРё СЃ РіР°СѓСЃСЃРѕРІРѕР№ С„СѓРЅРєС†РёРµР№ 
 115 вЂ” РІРµСЃРѕРІРѕР№ РєРѕСЌС„С„РёС†РёРµРЅС‚, 4 вЂ” С‡РёСЃР»Рѕ РїРёРєСЃРµР»РµР№ РІ РѕРєСЂРµСЃС‚РЅРѕСЃС‚Рё: */
 
 medianBlur(img_, img_, 11); // РјРµРґРёР°РЅРЅРѕРµ СЃРіР»Р°Р¶РёРІР°РЅРёРµ - СЃРѕС…СЂР°РЅСЏРµС‚ РєСЂР°СЏ, СѓРґР°Р»СЏСЏ С€СѓРј.
 /* img_ вЂ” РёСЃС…РѕРґРЅС‹Р№ РјР°СЃСЃРёРІ(РёР·РѕР±СЂР°Р¶РµРЅРёРµ), img_ вЂ” С†РµР»РµРІРѕР№ РјР°СЃСЃРёРІ
 11 вЂ” Р»РёРЅРµР№РЅС‹Р№ СЂР°Р·РјРµСЂ Р°РїРµСЂС‚СѓСЂС‹, РЅР°СЃРєРѕР»СЊРєРѕ СЃРёР»СЊРЅРѕРµ СЃРіР»Р°Р¶РёРІР°РЅРёРµ */
 
 copyMakeBorder(img_, img_, BORDER_SIZE, BORDER_SIZE, BORDER_SIZE, BORDER_SIZE, BORDER_CONSTANT, Scalar(0)); // РіСЂР°РЅРёС†Р° РІРѕРєСЂСѓРі РёР·РѕР±СЂР°Р¶РµРЅРёСЏ 
 /* img_ вЂ” РёСЃС…РѕРґРЅС‹Р№ РјР°СЃСЃРёРІ(РёР·РѕР±СЂР°Р¶РµРЅРёРµ), img_ вЂ” С†РµР»РµРІРѕР№ РјР°СЃСЃРёРІ
 BORDER_SIZE РІРµСЂС…РЅСЏСЏ , РЅРёР¶РЅСЏСЏ , Р»РµРІР°СЏ , РїСЂР°РІР°СЏ РіСЂР°РЅРёС†С‹ РІ РїРёРєСЃРµР»СЏС…
 BORDER_CONSTANT вЂ” РґРѕР±Р°РІР»СЏРµС‚ РїРѕСЃС‚РѕСЏРЅРЅСѓСЋ С†РІРµС‚РЅСѓСЋ СЂР°РјРєСѓ, value вЂ” С†РІРµС‚ РіСЂР°РЅРёС†С‹ (С‡РµСЂРЅС‹Р№) */
 
 Canny(img_, img_, 100, 250); // РґРµС‚РµРєС‚РѕСЂ РіСЂР°РЅРёС†
 /* img_ вЂ” РѕРґРЅРѕРєР°РЅР°Р»СЊРЅРѕРµ РёР·РѕР±СЂР°Р¶РµРЅРёРµ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё (РіСЂР°РґР°С†РёРё СЃРµСЂРѕРіРѕ), img_ вЂ” РѕРґРЅРѕРєР°РЅР°Р»СЊРЅРѕРµ РёР·РѕР±СЂР°Р¶РµРЅРёРµ РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РіСЂР°РЅРёС†, РЅР°Р№РґРµРЅРЅС‹С… С„СѓРЅРєС†РёРµР№
 100 вЂ” РїРѕСЂРѕРі РјРёРЅРёРјСѓРјР°, 250 вЂ” РїРѕСЂРѕРі РјР°РєСЃРёРјСѓРјР° */
 int max_contour_area = (img_.rows - BORDER_SIZE * 2) * (img_.cols - BORDER_SIZE * 2);
 int min_contour_area = (img_.rows / 2) * (img_.cols / 2);
 
 vector<vector<Point>> cont; // С…СЂР°РЅРёР»РёС‰Рµ РїР°РјСЏС‚Рё РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РґР°РЅРЅС‹С… РЅР°Р№РґРµРЅРЅС‹С… РєРѕРЅС‚СѓСЂРѕРІ
 vector<Vec4i> hierarchy;
 findContours(img_, cont, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
 /* img_ вЂ” РёСЃС…РѕРґРЅРѕРµ РёР·РѕР±СЂР°Р¶РµРЅРёРµ, cont вЂ” С…СЂР°РЅРёР»РёС‰Рµ РїР°РјСЏС‚Рё РґР»СЏ С…СЂР°РЅРµРЅРёСЏ РґР°РЅРЅС‹С… РЅР°Р№РґРµРЅРЅС‹С… РєРѕРЅС‚СѓСЂРѕРІ
 hierarchy - РёРµСЂР°СЂС…РёСЏ РІР»РѕР¶РµРЅРЅС‹С… РєРѕРЅС‚СѓСЂРѕРІ
 RETR_TREE вЂ” РЅР°Р№С‚Рё РІСЃРµ РєРѕРЅС‚СѓСЂС‹ Рё СЂР°Р·РјРµСЃС‚РёС‚СЊ РёС… РІ РёРµСЂР°СЂС…РёРё РІР»РѕР¶РµРЅРЅС‹С… РєРѕРЅС‚СѓСЂРѕРІ
 CHAIN_APPROX_SIMPLE вЂ” СЃР¶РёРјР°РµС‚ РіРѕСЂРёР·РѕРЅС‚Р°Р»СЊРЅС‹Рµ, РІРµСЂС‚РёРєР°Р»СЊРЅС‹Рµ Рё РґРёР°РіРѕРЅР°Р»СЊРЅС‹Рµ СЃРµРіРјРµРЅС‚С‹ Рё РѕСЃС‚Р°РІР»СЏРµС‚ С‚РѕР»СЊРєРѕ РёС… РєРѕРЅРµС‡РЅС‹Рµ С‚РѕС‡РєРё*/
 
 vector<Point> rcont;
	for (int i = 0; i < cont.size(); ++i) 
	  {
    	auto lenc = arcLength(cont[i], true);
		vector<Point2i> poly;
		approxPolyDP(cont[i], poly, 0.05 * lenc, true);
		auto contr = contourArea(poly);
		if (poly.size() == 4 && max_contour_area > contr&& contr > min_contour_area) rcont = poly;
      }

	for (int i = 0; i < rcont.size(); ++i) 
	  {
		rcont[i].x -= (rcont[i].x > BORDER_SIZE) ? BORDER_SIZE : rcont[i].x;
		rcont[i].y -= (rcont[i].y > BORDER_SIZE) ? BORDER_SIZE : rcont[i].y;
	  }
 return rcont;
}


struct corners_sorted {
	cv::Point2f top_left, top_right, bot_left, bot_right;
	bool empty;
	corners_sorted() { empty = true; }
};


corners_sorted sort_corners(std::vector<cv::Point> corners) {
	corners_sorted scors;
	if (corners.empty() || corners.size() != 4) return scors;
	std::sort(corners.begin(), corners.end(), [](const cv::Point& a, const cv::Point& b) -> bool {return(a.x < b.x); });

	if (corners[0].y < corners[1].y) {
		std::swap(corners[0], corners[1]);
	}
	scors.bot_left.x = float(corners[0].x);
	scors.bot_left.y = float(corners[0].y);
	scors.top_left.x = float(corners[1].x);
	scors.top_left.y = float(corners[1].y);

	if (corners[2].y < corners[3].y) {
		std::swap(corners[2], corners[3]);
	}
	scors.bot_right.x = float(corners[2].x);
	scors.bot_right.y = float(corners[2].y);
	scors.top_right.x = float(corners[3].x);
	scors.top_right.y = float(corners[3].y);

	scors.empty = false;
	return scors;
}


cv::Mat geo_resrore(cv::Mat& src, corners_sorted cs, int widthr, int heightr) {
	std::vector<cv::Point2f> cv = {
		cs.top_left, cs.bot_left, cs.bot_right, cs.top_right
	};

	std::vector<cv::Point2f> rv = {
		cv::Point2f((float)0,(float)0), cv::Point2f((float)0,(float)heightr - 1), cv::Point2f((float)widthr - 1, (float)heightr - 1), cv::Point2f((float)widthr - 1, (float)0)
	};

	cv::Mat rmat;
	auto pt = cv::getPerspectiveTransform(cv, rv);
	cv::warpPerspective(src, rmat, pt, cv::Size(widthr, heightr));

	return rmat;
}

int sum_cur_pix(const cv::Mat& img, uchar pix) {
	int summ = 0;
	for (int i = 0; i < img.rows; ++i) {
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == pix) summ++;
		}
	}
	return summ;
}


cv::Point2f area_marker_find(const cv::Mat& img, int marker_size) {
	std::vector<int> imctr(img.cols * img.rows, 0);

	int cpx, cpy = cpx = 0;

	for (int i = 0; i < img.rows - marker_size; ++i) {

		int bp = 0;
		cpx = 0;

		bp = sum_cur_pix(img(cv::Rect(0, cpy, marker_size, marker_size)), 0);

		imctr[cpx + cpy * img.cols] = bp;
		cpx++;

		for (int j = 0; j < img.cols - marker_size; ++j) {
			int minus_pts = 0;
			for (int k = 0; k < marker_size; ++k) {
				if (img.at<uchar>(i + k, j) == 0) minus_pts++;
			}

			int plus_pts = 0;
			for (int k = 0; k < marker_size; ++k) {
				if (img.at<uchar>(i + k, j + marker_size - 1) == 0) plus_pts++;
			}

			bp = bp - minus_pts + plus_pts;
			imctr[cpx + cpy * img.cols] = bp;
			cpx++;
		}
		cpy++;
	}

	auto mv = *(std::max_element(imctr.begin(), imctr.end()));

	int cnt = 0; int px = 0; int py = 0;

	for (int i = 0; i < img.cols; ++i) {
		for (int j = 0; j < img.rows; ++j) {
			if (imctr[i + j * img.cols] != mv) continue;
			px += i;
			py += j;
			cnt++;
		}
	}

	float padding = (float)marker_size / 2;
	return cv::Point2f((float)px / cnt + padding, (float)py / cnt + padding);
}


corners_sorted find_markers(cv::Mat& img_) {
	cv::adaptiveThreshold(img_, img_, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 55, 4);
	corners_sorted cs;
	// ГЅГЄГ±ГЇГҐГ°ГЁГ¬ГҐГГІГ Г«ГјГГ® ГЇГ®Г«ГіГ·ГҐГГ® Г·ГІГ® Г°Г Г§Г¬ГҐГ° Г¬Г Г°ГЄГҐГ°Г  ГГ  ГґГ®ГІГ® ГЇГ°ГЁ Г°Г Г§Г¬ГҐГ°Г Гµ 1500 ГГ  1000 ГЇГЁГЄГ±ГҐГ«ГҐГ© 37 ГГ  37;
	cs.top_left = area_marker_find(img_(cv::Rect2i(0, 0, 200, 500)), 37);

	cs.bot_left = area_marker_find(img_(cv::Rect2i(0, 500, 200, 500)), 37);
	cs.bot_left.y += 500;

	cs.top_right = area_marker_find(img_(cv::Rect2i(img_.cols - 201, 0, 200, 500)), 37);
	cs.top_right.x += img_.cols - 201;

	cs.bot_right = area_marker_find(img_(cv::Rect2i(img_.cols - 201, 500, 200, 500)), 37);
	cs.bot_right.x += img_.cols - 201;
	cs.bot_right.y += 500;

	cs.empty = false;
	return cs;
}


void shadow_deleter_binariser(cv::Mat& img) {
	auto k = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
	cv::Mat img_;
	cv::dilate(img, img_, k);
	cv::medianBlur(img_, img_, 11);
	cv::absdiff(img, img_, img);
	for (int i = 0; i < img.cols; ++i) {
		for (int j = 0; j < img.rows; ++j) {
			img.at<uchar>(j, i) = 255 - img.at<uchar>(j, i);
		}
	}

	cv::normalize(img, img, 0, 255, cv::NORM_MINMAX, CV_8UC1);
	cv::adaptiveThreshold(img, img, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 77, 7);
}


int lineposrestore(const cv::Mat& farea, int thresh) {
	std::vector<int> histy(farea.rows, 0);
	for (int i = 0; i < farea.rows; ++i) {
		for (int j = 0; j < farea.cols; ++j) {
			if (farea.at<uchar>(i, j) == 0) histy[i]++;
		}
	}

	auto a = (int)(std::distance(histy.begin(), std::max_element(histy.begin(), histy.end())));
	return (a > thresh) ? a : -1;
}


void delete_noise(cv::Mat& img, int kern, int yb, int ye) {
	for (int j = yb; j < ye - kern - 2; ++j) {
		for (int i = 0; i < img.cols - kern - 2; ++i) {
			bool hfind = false;
			for (int k = 0; k < kern + 2; ++k) {
				if (img.at<uchar>(j, i + k) == 0 || img.at<uchar>(j + kern + 1, i + k) == 0) {
					i += k;
					hfind = true;
					break;
				}

				if (img.at<uchar>(j + k, i) == 0 || img.at<uchar>(j + k, i + kern + 1) == 0) {
					hfind = true;
					break;
				}

			}

			if (!hfind) {
				cv::rectangle(img, cv::Rect(i + 1, j + 1, kern, kern), cv::Scalar(255), -1);
				i += kern + 1;
			}

		}
	}
}


void ppl(cv::Mat&& img, int& linepos, int& lineposx) {

	delete_noise(img, 2, 0, img.rows);
	int sm = 0;
	linepos = -1;
	lineposx = -1;
	std::vector<int> histy(img.rows, 0), histx(img.cols, 0);

	for (int i = 0; i < img.rows; ++i) { //Г±Г·ГЁГІГ ГҐГ¬ ГЈГЁГ±ГІГі
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == 255) { histy[i]++; histx[j]++; }
		}
	}

	int line_thresh = img.cols * 0.6; //ГЇГ°Г®ГЇГ®Г«ГЄГ  ГЇГ® y
	int lt_count = 0, lt_pos = 0;
	for (int i = 0; i < histy.size() / 4; ++i) {
		if (histy[i] > line_thresh) {
			cv::line(img, cv::Point(0, i), cv::Point(img.cols, i), cv::Scalar(0), 1);
			++lt_count; lt_pos += i;
		}
	}
	if (lt_count > 0) {
		linepos = (int)(lt_pos / lt_count);
	}

	for (int i = histy.size() * 3 / 4; i < histy.size(); ++i) {
		if (histy[i] > line_thresh) {
			cv::line(img, cv::Point(0, i), cv::Point(img.cols, i), cv::Scalar(0), 1);
		}
	}


	line_thresh = img.rows * 0.6; //ГЇГ°Г®ГЇГ®Г«ГЄГ  ГЇГ® X
	lt_count = 0, lt_pos = 0;
	for (int i = 0; i < histx.size() / 10; ++i) {
		if (histx[i] > line_thresh) {
			cv::line(img, cv::Point(i, 0), cv::Point(i, img.rows), cv::Scalar(0), 1);
		}
	}

	for (int i = histx.size() - 8; i < histx.size(); ++i) {
		if (histx[i] > line_thresh) {
			cv::line(img, cv::Point(i, 0), cv::Point(i, img.rows), cv::Scalar(0), 1);
			++lt_count; lt_pos += i;
		}
	}
	if (lt_count > 0) {
		lineposx = img.cols - (int)(lt_pos / lt_count);
	}


}


int is_plus(cv::Mat&& img) {

	std::vector<int> histy_(img.rows, 0), histx_(img.cols, 0);
	for (int i = 0; i < img.rows; ++i) { //Г±Г·ГЁГІГ ГҐГ¬ ГЈГЁГ±ГІГі
		for (int j = 0; j < img.cols; ++j) {
			if (img.at<uchar>(i, j) == 255) { histy_[i]++; histx_[j]++; }
		}
	}

	int btp = 0, endp = img.cols;

	while (abs(endp - btp) > 1) {
		int ck = (endp + btp) / 2;
		int sml = 0, smr = 0;
		for (int i = btp; i < ck; i++) {
			sml += histx_[i];
		}
		for (int i = ck; i < endp; i++) {
			smr += histx_[i];
		}
		if (sml > smr) {
			endp = ck;
		}
		else {
			btp = ck;
		}
	}
	int ost = 0;
	btp -= 15;
	if (btp < 0) {
		ost = -1 * btp;
		btp = 0;
	}
	endp += 15 + ost;
	if (endp > img.cols - 1) {
		int add = endp - img.cols + 1;
		ost -= add;
		endp = img.cols - 1;
	}

	auto rr = img(cv::Rect(btp, 0, endp - btp, img.rows));

	std::vector<std::vector<cv::Point>> cntr;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(rr, cntr, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	if (cntr.size() == 0) return 0;

	bool pfind = false;

	for (int i = 0; i < cntr.size(); ++i) {
		if (cntr[i].size() < 2) continue;

		std::sort(cntr[i].begin(), cntr[i].end(), [](const cv::Point& a, const cv::Point& b) -> bool { return (a.y < b.y); });
		cv::Point yd = cntr[i][0];
		cv::Point ye = cntr[i][cntr[i].size() - 1];

		std::sort(cntr[i].begin(), cntr[i].end(), [](const cv::Point& a, const cv::Point& b) -> bool { return (a.x < b.x); });

		cv::Point xd = cntr[i][0];
		cv::Point xe = cntr[i][cntr[i].size() - 1];

		if (abs(yd.y - ye.y) < 3) continue;
		if (abs(xd.x - xe.x) < 3) continue;
		if (sqrt(pow(xd.y - yd.y, 2) + pow(xd.x - yd.x, 2)) < 3) continue;
		if (sqrt(pow(xe.y - ye.y, 2) + pow(xe.x - ye.x, 2)) < 3) continue;

		pfind = true;
		break;
	}


	if (!pfind) return 0;
#ifdef TEST_TO_SEE_RECOG

	cv::bitwise_not(img, img);
	for (int i = 0; i < img.cols; ++i) {
		for (int j = 0; j < img.rows; ++j) {
			if (img.at<uchar>(j, i) == 255) img.at<uchar>(j, i) = 55;
			if (img.at<uchar>(j, i) == 0) img.at<uchar>(j, i) = 155;
		}
	}
#endif // TEST_TO_SEE_RECOG
	return 1;
}


std::vector<std::vector<int>> find_pluses(cv::Mat& img) {

	delete_noise(img, 2, 0, 80);
	delete_noise(img, 4, 0, 80);
	delete_noise(img, 6, 0, 80);

	std::vector<int> f_line_pos(TABLE_COLS, 0);
	int begin_position_f_line = 270;
	int find_range = 30;

	for (int i = 0; i < TABLE_COLS; ++i) {
		int pos = -1;
		int cr = 0;
		int add_range = 0;
		while (pos == -1 && cr++ != 2) {
			pos = lineposrestore(img(cv::Rect(begin_position_f_line, 15, find_range, 50 + add_range)), (int)(find_range / 1.2));
			add_range = 25;
		}
		add_range = 0;
		cr = 0;
		if (pos == -1) {
			while (pos == -1 && cr++ != 2) {
				pos = lineposrestore(img(cv::Rect(begin_position_f_line, 15, find_range, 50 + add_range)), (int)(find_range / 1.5));
				add_range = 20;
			}
		}
		if (pos == -1) return std::vector<std::vector<int>>();
		f_line_pos[i] = pos + 15;
		begin_position_f_line += 105;
	}

	cv::bitwise_not(img, img);
	std::vector<std::vector<int>> retvec;
	for (int i = 0; i < TABLE_ROWS; ++i) retvec.push_back(std::vector<int>(TABLE_COLS, 0));
	int begy = 40;
	int begx = 230;
	const int recwidth = 110;
	const float recheight_ = 28;
	const int paddingx = 5;
	const int paddingy = 2;

	for (int i = 0; i < TABLE_COLS; ++i) {
		int bp = f_line_pos[i];
		int recheight = (int)(std::round(recheight_ + (float)(begy - bp) / TABLE_ROWS));
		std::vector<int> pv(TABLE_ROWS, 0);
		for (int k = 0; k < TABLE_ROWS; ++k) {
			int lineypos, linexpos;
			if (bp - paddingy + recheight > img.rows) bp = img.rows - 1 - recheight + paddingy;
			if (begx + recwidth > img.cols) begx = img.cols - 1 - recwidth;
			ppl(img(cv::Rect(begx + paddingx, bp + paddingy, recwidth - 2 * paddingx, recheight - paddingy * 2)), lineypos, linexpos);
			if (lineypos != -1) bp += lineypos + paddingy;
			if (linexpos != -1) begx -= (paddingx + linexpos);
			pv[k] = bp;
			bp += recheight;
		}
		for (int k = 0; k < TABLE_ROWS; ++k) {
			int lineypos, linexpos;
			ppl(img(cv::Rect(begx + paddingx, pv[k] + paddingy, recwidth - 2 * paddingx, recheight - paddingy * 2)), lineypos, linexpos);
		}

		for (int j = 0; j < TABLE_ROWS; ++j) {
			retvec[j][i] = is_plus(img(cv::Rect(begx + paddingx, pv[j] + paddingy, recwidth - 2 * paddingx, recheight - paddingy * 2)));
		}
		begx += recwidth;

	}
	return retvec;
}



Recognizer::Recognizer(){

}

void Recognizer::load(string fname){
	img = cv::imread(fname, cv::IMREAD_COLOR);
}

vector<vector<int>> Recognizer::recognise()
{
    vector<vector<int>> res;
	resize_to_wsize(img);
	cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
	cv::Mat img_;
	img.copyTo(img_);

	auto cornrs = find_list_corners(img_);
	auto scornrs = sort_corners(cornrs);


	if (scornrs.empty) {
		return res;
	}

	img = geo_resrore(img, scornrs, WIDTH_A4_LIST, HEIGHT_A4_LIST);
	img.copyTo(img_);

	scornrs = find_markers(img_);
	img = geo_resrore(img, scornrs, WIDTH_TABLE_LIST, HEIGHT_TABLE_LIST);
	shadow_deleter_binariser(img);

	res = find_pluses(img);
	return res;
 
}