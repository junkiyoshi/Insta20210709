#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	for (int x = -300; x <= 300; x += 20) {

		for (int y = -300; y <= 300; y += 20) {

			this->location_list.push_back(glm::vec2(x, y));
			this->angle_list.push_back(0);
			this->color_list.push_back(ofColor(0));
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	vector<ofColor> base_color_list;
	base_color_list.push_back(ofColor(255, 0, 0));
	base_color_list.push_back(ofColor(0, 255, 0));
	base_color_list.push_back(ofColor(0, 0, 255));

	for (int k = 0; k < base_color_list.size(); k++) {

		auto noise_param = glm::vec2(ofRandom(1000), ofRandom(1000));
		auto location = glm::vec2(ofMap(ofNoise(noise_param.x, ofGetFrameNum() * 0.03), 0, 1, -400, 400), ofMap(ofNoise(noise_param.y, ofGetFrameNum() * 0.03), 0, 1, -400, 400));
		auto next = glm::vec2(ofMap(ofNoise(noise_param.x, (ofGetFrameNum() + 1) * 0.03), 0, 1, -400, 400), ofMap(ofNoise(noise_param.y, (ofGetFrameNum() + 1) * 0.03), 0, 1, -400, 400));
		auto angle = std::atan2(next.y - location.y, next.x - location.x);

		for (int i = 0; i < this->location_list.size(); i++) {

			auto distance = glm::distance(this->location_list[i], location);
			if (distance < 40) {

				this->angle_list[i] = angle;
				this->color_list[i] += base_color_list[k];
			}
		}
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		this->color_list[i].r = this->color_list[i].r > 6 ? this->color_list[i].r - 6 : 0;
		this->color_list[i].g = this->color_list[i].g > 6 ? this->color_list[i].g - 6 : 0;
		this->color_list[i].b = this->color_list[i].b > 6 ? this->color_list[i].b - 6 : 0;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->location_list.size(); i++) {

		ofColor tmp_color = this->color_list[i];
		tmp_color.r = tmp_color.r > 128 ? 255 : ofMap(tmp_color.r, 0, 128, 0, 255);
		tmp_color.g = tmp_color.g > 128 ? 255 : ofMap(tmp_color.g, 0, 128, 0, 255);
		tmp_color.b = tmp_color.b > 128 ? 255 : ofMap(tmp_color.b, 0, 128, 0, 255);
		this->draw_arrow(this->location_list[i], this->location_list[i] + glm::vec2(cos(this->angle_list[i]), sin(this->angle_list[i])), 13, ofColor(255), tmp_color);
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size, ofColor fill_color, ofColor no_fill_color) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);

	ofSetColor(fill_color);
	ofFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();

	ofSetColor(no_fill_color);
	ofNoFill();
	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)));
	ofVertex(location + glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)));
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofEndShape();

	ofBeginShape();
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle - PI * 0.5), size * 0.5 * sin(angle - PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25 - glm::vec2(size * cos(angle), size * sin(angle)) * 0.5);
	ofVertex(location + glm::vec2(size * 0.5 * cos(angle + PI * 0.5), size * 0.5 * sin(angle + PI * 0.5)) * 0.25);
	ofEndShape();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}