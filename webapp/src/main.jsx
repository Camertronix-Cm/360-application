import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom'
import { Home } from './pages/home.jsx'

createRoot(document.getElementById('root')).render(
  <StrictMode>
    <Router>
      <Switch>
        <Route exact path="/">
          <Home />
        </Route>
      </Switch>
    </Router>
  </StrictMode>,
)
