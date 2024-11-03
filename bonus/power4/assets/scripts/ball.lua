local picked = false
local canBePicked = true

function update(registry, gameContext)
    local x, y = getPosition()
    local mouseX, mouseY = getMousePosition()

    if not canBePicked then
        return
    end
    if getKeyDown("Mouse0") then
        if mouseX > x and mouseX < x + 100 and mouseY > y and mouseY < y + 100 then
            picked = true
        end
    end
    if getKeyUp("Mouse0") then
        picked = false
    end
    if picked then
        setPosition(mouseX - 50, mouseY - 50)
        setRigidBody(0, 0)
    end
end

function events(registry, gameContext)
    if hasEvent("triggerColumn") then
        picked = false
        canBePicked = false
    end
end