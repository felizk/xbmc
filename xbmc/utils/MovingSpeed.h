/*
 *  Copyright (C) 2022 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include <map>
#include <stdint.h>

namespace UTILS
{
namespace MOVING_SPEED
{
struct EventCfg
{
  /*!
   * \param acceleration Acceleration in pixels per second (px/sec)
   * \param maxVelocity Max movement speed, it depends from acceleration value,
   *        a suitable value could be (acceleration value)*3. Set 0 to disable it
   * \param resetTimeout Resets acceleration speed if idle for specified millisecs
   */
  EventCfg(float acceleration, float maxVelocity, uint32_t resetTimeout)
    : m_acceleration{acceleration}, m_maxVelocity{maxVelocity}, m_resetTimeout{resetTimeout}
  {
  }

  float m_acceleration;
  float m_maxVelocity;
  uint32_t m_resetTimeout;
};

/*!
 * \brief Class to calculate the velocity for a motion effect.
 * To ensure it works, the GetUpdatedDistance method must be called at each
 * input received (e.g. continuous key press of same key on the keyboard).
 * The motion effect will stop at the event ID change (different key pressed).
 */
class CMovingSpeed
{
public:
  /*!
   * \brief Add the configuration for an event
   * \param eventId The id for the event, must be unique
   * \param acceleration Acceleration in pixels per second (px/sec)
   * \param maxVelocity Max movement speed, it depends from acceleration value,
   *        a suitable value could be (acceleration value)*3. Set 0 to disable it
   * \param resetTimeout Resets acceleration speed if idle for specified millisecs
   */
  void AddEventConfig(uint32_t eventId,
                      float acceleration,
                      float maxVelocity,
                      uint32_t resetTimeout);

  /*!
   * \brief Add the configuration for an event
   * \param event The event configuration
   */
  void AddEventConfig(uint32_t eventId, EventCfg event);

  /*!
   * \brief Reset stored velocity to all events
   * \param event The event configuration
   */
  void Reset();

  /*!
   * \brief Reset stored velocity for a specific event
   * \param event The event ID
   */
  void Reset(uint32_t eventId);

  /*!
   * \brief Get the updated distance based on acceleration speed
   * \param eventId The id for the event to handle
   * \return The distance
   */
  float GetUpdatedDistance(uint32_t eventId);

private:
  struct EventData
  {
    EventData(EventCfg config) : m_config{config} {}

    EventCfg m_config;
    float m_currentVelocity{1.0f};
    uint32_t m_lastFrameTime{0};
  };

  uint32_t m_currentEventId{0};
  std::map<uint32_t, EventData> m_eventsData;
};

} // namespace MOVING_SPEED
} // namespace UTILS
