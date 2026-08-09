// helloooooo
// this is my source code :)
// hope u like this

#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <array>
#include <vector>
#include <random>

using namespace geode::prelude;

class $modify(RotatingPlayLayer, PlayLayer) {

    // a unique tag lol
    static constexpr int ROTATION_TIMER_TAG = 0x90431;
    static constexpr int ROTATION_ANIMATION_TAG = 0x90432;

    struct Fields {
        float m_currentAngle = 0.f;
    };

    // reuse rng instance
    static std::mt19937& getRNG() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    float pickRandomAngle(float currentAngle) {
        std::array<float, 4> angles = { 0.f, 90.f, 180.f, 270.f };
        std::vector<float> available;
        
        for (float angle : angles) {
            if (angle != currentAngle) {
                available.push_back(angle);
            }
        }

        std::uniform_int_distribution<> dis(0, available.size() - 1);
        return available[dis(getRNG())];
    }

    void scheduleNextRotation() {
        // Stop only the pending timer action, leaving active rotations untouched
        this->stopActionByTag(ROTATION_TIMER_TAG);

        float minInterval = Mod::get()->getSettingValue<double>("min-interval");
        float maxInterval = Mod::get()->getSettingValue<double>("max-interval");

        if (maxInterval < minInterval) maxInterval = minInterval + 1.f;

        std::uniform_real_distribution<float> dis(minInterval, maxInterval);
        float delay = dis(getRNG());

        auto action = CCSequence::create(
            CCDelayTime::create(delay),
            CCCallFunc::create(this, callfunc_selector(RotatingPlayLayer::doRandomRotation)),
            nullptr
        );
        
        action->setTag(ROTATION_TIMER_TAG);
        this->runAction(action);
    }

    void doRandomRotation() {
        if (this->m_isPaused) {
            scheduleNextRotation();
            return;
        }

        float newAngle = pickRandomAngle(m_fields->m_currentAngle);
        m_fields->m_currentAngle = newAngle;

        float rotDuration = Mod::get()->getSettingValue<double>("rotation-speed");

        // stop current animation yayy (lol)
        this->stopActionByTag(ROTATION_ANIMATION_TAG);

        auto rotAction = CCRotateTo::create(rotDuration, m_fields->m_currentAngle);
        rotAction->setTag(ROTATION_ANIMATION_TAG);
        this->runAction(rotAction);

        scheduleNextRotation();
    }

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;

        m_fields->m_currentAngle = 0.f;
        scheduleNextRotation();

        return true;
    }

    void resetLevel() {
        PlayLayer::resetLevel();

	// clean up running actions :D
        this->stopActionByTag(ROTATION_TIMER_TAG);
        this->stopActionByTag(ROTATION_ANIMATION_TAG);
        
        this->setRotation(0.f);
        m_fields->m_currentAngle = 0.f;

        scheduleNextRotation();
    }
};

// thanks for reading :)